<?php
$conn = new mysqli("localhost", "root", "", "motor_control");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if (isset($_POST['command'])) {
    $command = $_POST['command'];
    $stmt = $conn->prepare("INSERT INTO commands (command) VALUES (?)");
    $stmt->bind_param("s", $command);
    $stmt->execute();
    echo "Command saved: " . $command;
    $stmt->close();
} else {
    echo "No command received";
}

$conn->close();
?>
