#include <Node.h>

#include <MConnection.h>
#include <MLight.h>
#include <MLdr.h>
#include <MMovementSensor.h>

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

PositionMac *peerMACs = new PositionMac();

class NodeTest : public ::testing::Test
{
protected:
    NodeTest()
        : node(peerMACs, connection, light, lightSensor, movementSensor)
    {
    }

    virtual ~NodeTest() {}

    MLight light;
    MConnection connection;
    MLdr lightSensor;
    MMovementSensor movementSensor;

    Node node;
};

TEST_F(NodeTest, test_change_to_night)
{
    node.state = DAY;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(300));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(true));
    EXPECT_EQ(NIGHT, node.HandleStates());
}

TEST_F(NodeTest, test_change_to_day)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(500));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(true));
    EXPECT_EQ(DAY, node.HandleStates());
}

TEST_F(NodeTest, test_hardware_error)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(500));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(false));
    EXPECT_EQ(HARDWARE_ERROR, node.HandleStates());
}

TEST_F(NodeTest, test_connection_error_detection)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(300));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(true));
    EXPECT_CALL(movementSensor, DetectMovement()).WillOnce(Return(true));
    EXPECT_CALL(light, AdjustLightIntensity(LEVEL5));
    EXPECT_CALL(connection, GetSentStatus()).WillOnce(Return(false));
    EXPECT_EQ(CONNECTION_ERROR_DETECTION, node.HandleStates());
}

TEST_F(NodeTest, test_detect_movement)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(300));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(true));
    EXPECT_CALL(movementSensor, DetectMovement()).WillOnce(Return(true));
    EXPECT_CALL(light, AdjustLightIntensity(LEVEL5));
    EXPECT_CALL(connection, GetSentStatus()).WillOnce(Return(true));
    EXPECT_EQ(NIGHT, node.HandleStates());
}

TEST_F(NodeTest, test_connection_error)
{
    node.state = CONNECTION_ERROR_DETECTION;
    EXPECT_CALL(connection, GetSentStatus()).WillRepeatedly(Return(false));
    EXPECT_EQ(CONNECTION_ERROR, node.HandleStates());
}

TEST_F(NodeTest, test_connection_error_in_middle)
{
    node.lastState = NIGHT;
    node.state = CONNECTION_ERROR;
    node.mostLeftNode = false;
    node.mostRightNode = false;
    EXPECT_CALL(connection, GetSentStatus()).WillRepeatedly(Return(false));
    EXPECT_CALL(connection, SendData(_)).Times(2);
    EXPECT_EQ(NIGHT, node.HandleStates());
}

TEST_F(NodeTest, test_connection_error_most_left)
{
    node.lastState = NIGHT;
    node.state = CONNECTION_ERROR;
    node.mostLeftNode = true;
    node.mostRightNode = false;
    EXPECT_CALL(connection, GetSentStatus()).WillRepeatedly(Return(false));
    EXPECT_CALL(connection, SendData(_)).Times(1);
    EXPECT_EQ(NIGHT, node.HandleStates());
}

TEST_F(NodeTest, test_connection_error_most_right)
{
    node.lastState = NIGHT;
    node.state = CONNECTION_ERROR;
    node.mostLeftNode = false;
    node.mostRightNode = true;
    EXPECT_CALL(connection, GetSentStatus()).WillRepeatedly(Return(false));
    EXPECT_CALL(connection, SendData(_)).Times(1);
    EXPECT_EQ(NIGHT, node.HandleStates());
}

TEST_F(NodeTest, test_hardware_error_no_recovery)
{
    node.state = HARDWARE_ERROR;
    EXPECT_CALL(connection, SendData(_)).Times(AtLeast(1));
    node.HandleStates();
    EXPECT_EQ(HARDWARE_ERROR, node.state);
}

TEST_F(NodeTest, test_light_check_fail_in_day)
{
    node.state = DAY;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(300));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(false));
    EXPECT_EQ(HARDWARE_ERROR, node.HandleStates());
}

TEST_F(NodeTest, test_unexpected_state_transition)
{
    node.state = static_cast<States>(999);
    EXPECT_EQ(999, node.HandleStates());
}

TEST_F(NodeTest, test_idle_to_day)
{
    node.state = IDLE;
    EXPECT_EQ(DAY, node.HandleStates());
}

TEST_F(NodeTest, test_night_movement_no_connection)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(300));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(true));
    EXPECT_CALL(movementSensor, DetectMovement()).WillOnce(Return(true));
    EXPECT_CALL(light, AdjustLightIntensity(LEVEL5));
    EXPECT_CALL(connection, SendData(_)).Times(1);
    EXPECT_CALL(connection, GetSentStatus()).WillOnce(Return(false));
    EXPECT_EQ(CONNECTION_ERROR_DETECTION, node.HandleStates());
}

TEST_F(NodeTest, test_connection_error_detection_retry_success)
{
    node.state = CONNECTION_ERROR_DETECTION;
    EXPECT_CALL(connection, SendData(_)).Times(AtLeast(1));
    EXPECT_CALL(connection, GetSentStatus())
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_EQ(NIGHT, node.HandleStates());
}

TEST_F(NodeTest, test_connection_error_detection_retry_fail)
{
    node.state = CONNECTION_ERROR_DETECTION;
    EXPECT_CALL(connection, SendData(_)).Times(5);
    EXPECT_CALL(connection, GetSentStatus()).WillRepeatedly(Return(false));
    EXPECT_EQ(CONNECTION_ERROR, node.HandleStates());
}

TEST_F(NodeTest, test_idle_state_ignores_sensors)
{
    node.state = IDLE;
    EXPECT_CALL(lightSensor, ReadLightLevel()).Times(0);
    EXPECT_CALL(light, LightCheck()).Times(0);
    EXPECT_CALL(movementSensor, DetectMovement()).Times(0);
    EXPECT_EQ(DAY, node.HandleStates());
}

TEST_F(NodeTest, test_light_sensor_fails_during_transition)
{
    node.state = DAY;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(-1));
    EXPECT_EQ(HARDWARE_ERROR, node.HandleStates());
}

TEST_F(NodeTest, test_hardware_error_recovery_multiple_retries)
{
    node.state = HARDWARE_ERROR;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillRepeatedly(Return(0));
    EXPECT_CALL(light, LightCheck()).WillRepeatedly(Return(false));
    EXPECT_EQ(HARDWARE_ERROR, node.HandleStates());
}

TEST_F(NodeTest, test_detect_movement_no_connection_error)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(300));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(true));
    EXPECT_CALL(movementSensor, DetectMovement()).WillOnce(Return(true));
    EXPECT_CALL(light, AdjustLightIntensity(LEVEL5));
    EXPECT_CALL(connection, GetSentStatus()).WillOnce(Return(true));
    EXPECT_EQ(NIGHT, node.HandleStates());
}

TEST_F(NodeTest, test_night_no_movement)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(300));
    EXPECT_CALL(light, LightCheck()).WillOnce(Return(true));
    EXPECT_CALL(movementSensor, DetectMovement()).WillOnce(Return(false));
    EXPECT_CALL(light, AdjustLightIntensity(_)).Times(0);
    EXPECT_EQ(NIGHT, node.HandleStates());
}
TEST_F(NodeTest, test_sensor_error_in_night)
{
    node.state = NIGHT;
    EXPECT_CALL(lightSensor, ReadLightLevel()).WillOnce(Return(-1));
    EXPECT_EQ(HARDWARE_ERROR, node.HandleStates());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
