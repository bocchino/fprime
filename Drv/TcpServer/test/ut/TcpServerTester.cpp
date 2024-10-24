// ======================================================================
// \title  TcpServerTester.cpp
// \author mstarch
// \brief  cpp file for TcpServerTester for TcpServer
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================
#include "TcpServerTester.hpp"
#include "STest/Pick/Pick.hpp"
#include "Os/Console.hpp"
#include <Drv/Ip/test/ut/PortSelector.hpp>
#include <Drv/Ip/test/ut/SocketTestHelper.hpp>

Os::Console logger;

namespace Drv {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

void TcpServerTester ::test_with_loop(U32 iterations, bool recv_thread) {
    U8 buffer[sizeof(m_data_storage)] = {};
    Drv::SocketIpStatus status1 = Drv::SOCK_SUCCESS;
    Drv::SocketIpStatus status2 = Drv::SOCK_SUCCESS;
    Drv::SocketIpStatus serverStat = Drv::SOCK_SUCCESS;

    U16 port =  0;
    NATIVE_INT_TYPE client_fd = -1;
    status1 = this->component.configure("127.0.0.1", port, 0, 100);
    EXPECT_EQ(status1, Drv::SOCK_SUCCESS);

    // Start up a receive thread
    if (recv_thread) {
        Os::TaskString name("receiver thread");
        this->component.start(name, true, Os::Task::TASK_DEFAULT, Os::Task::TASK_DEFAULT);
        EXPECT_TRUE(this->wait_on_started(true, Drv::Test::get_configured_delay_ms()/10 + 1));
    }
    EXPECT_TRUE(component.isStarted());

    // Loop through a bunch of client disconnects
    for (U32 i = 0; i < iterations && serverStat == SOCK_SUCCESS; i++) {
        Drv::TcpClientSocket client;
        client.configure("127.0.0.1", this->component.getListenPort(), 0, 100);
        status2 = client.open(client_fd);

        U32 size = sizeof(m_data_storage);

        // Not testing with reconnect thread, we will need to open ourselves
        if (not recv_thread) {
            status1 = this->component.open();
        } else {
            EXPECT_TRUE(this->wait_on_change(true, Drv::Test::get_configured_delay_ms()/10 + 1));
        }
        EXPECT_TRUE(this->component.isOpened());

        EXPECT_EQ(status1, Drv::SOCK_SUCCESS);
        EXPECT_EQ(status2, Drv::SOCK_SUCCESS);

        status2 = Drv::SOCK_NO_DATA_AVAILABLE;

        // If all the opens worked, then run this
        if ((Drv::SOCK_SUCCESS == status1) && (Drv::SOCK_SUCCESS == status2) &&
            (this->component.isOpened())) {
            // Force the sockets not to hang, if at all possible

            Drv::Test::force_recv_timeout(this->component.m_fd, this->component.getSocketHandler());
            Drv::Test::force_recv_timeout(client_fd, client);
            m_data_buffer.setSize(sizeof(m_data_storage));
            Drv::Test::fill_random_buffer(m_data_buffer);
            Drv::SendStatus status = invoke_to_send(0, m_data_buffer);
            EXPECT_EQ(status, SendStatus::SEND_OK);
            U16 counter = 0;
            while ((status2 == Drv::SOCK_NO_DATA_AVAILABLE) and counter < Drv::Test::MAX_ITER) {
                status2 = client.recv(client_fd, buffer, size);
                counter++;
            }
            EXPECT_EQ(status2, Drv::SOCK_SUCCESS);
            EXPECT_EQ(size, m_data_buffer.getSize());
            Drv::Test::validate_random_buffer(m_data_buffer, buffer);

            // If receive thread is live, try the other way
            if (recv_thread) {
                m_spinner = false;
                m_data_buffer.setSize(sizeof(m_data_storage));
                status2 = client.send(client_fd, m_data_buffer.getData(), m_data_buffer.getSize());
                EXPECT_EQ(status2, Drv::SOCK_SUCCESS);
                //from_deallocate_handler(0, m_data_buffer);
                while (not m_spinner) {}
            }
        }

        // Properly stop the client on the last iteration
        if (((1 + i) == iterations) && recv_thread) {
            this->component.stop();
            this->component.close();
            client.close(client_fd); // Client must be closed first or the server risks binding to an existing address
            this->component.shutdown();
            this->component.join();
        } else {
            this->component.close();
            client.close(client_fd); // Client must be closed first or the server risks binding to an existing address
        }
    }
    ASSERT_from_ready_SIZE(iterations);
}

bool TcpServerTester::wait_on_change(bool open, U32 iterations) {
    for (U32 i = 0; i < iterations; i++) {
        if (open == this->component.isOpened()) {
            return true;
        }
        Os::Task::delay(Fw::Time(0, 10000));
    }
    return false;
}


bool TcpServerTester::wait_on_started(bool open, U32 iterations) {
    for (U32 i = 0; i < iterations; i++) {
        if (open == this->component.isStarted()) {
            return true;
        }
        Os::Task::delay(Fw::Time(0, 10000));
    }
    return false;
}

TcpServerTester ::TcpServerTester()
    : TcpServerGTestBase("Tester", MAX_HISTORY_SIZE),
      component("TcpServer"),
      m_data_buffer(m_data_storage, 0), m_spinner(true) {
    this->initComponents();
    this->connectPorts();
    ::memset(m_data_storage, 0, sizeof(m_data_storage));
}

TcpServerTester ::~TcpServerTester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void TcpServerTester ::test_basic_messaging() {
    test_with_loop(1);
}

void TcpServerTester ::test_multiple_messaging() {
    test_with_loop(100);
}

void TcpServerTester ::test_receive_thread() {
    test_with_loop(1, true);
}

void TcpServerTester ::test_advanced_reconnect() {
    test_with_loop(10, true); // Up to 10 * RECONNECT_MS
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void TcpServerTester ::from_recv_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& recvBuffer, const RecvStatus& recvStatus) {
    // this function will still receive a status of error because the recv port is always called
    this->pushFromPortEntry_recv(recvBuffer, recvStatus);
    if (recvStatus == RecvStatus::RECV_OK){
        // Make sure we can get to unblocking the spinner
        EXPECT_EQ(m_data_buffer.getSize(), recvBuffer.getSize()) << "Invalid transmission size";
        Drv::Test::validate_random_buffer(m_data_buffer, recvBuffer.getData());
        m_spinner = true;
    }
    delete[] recvBuffer.getData();
}

void TcpServerTester ::from_ready_handler(const NATIVE_INT_TYPE portNum) {
    this->pushFromPortEntry_ready();
}

Fw::Buffer TcpServerTester ::
    from_allocate_handler(
        const NATIVE_INT_TYPE portNum,
        U32 size
    )
  {
    this->pushFromPortEntry_allocate(size);
    Fw::Buffer buffer(new U8[size], size);
    m_data_buffer2 = buffer;
    return buffer;
  }

  void TcpServerTester ::
    from_deallocate_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    this->pushFromPortEntry_deallocate(fwBuffer);
  }
}  // end namespace Drv
