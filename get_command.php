<?php
$conn = new mysqli("localhost", "root", "", "motor_control");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$result = $conn->query("SELECT command FROM commands ORDER BY id DESC LIMIT 1");
if ($row = $result->fetch_assoc()) {
    echo $row['command'];
} else {
    echo "no_command";
}

$conn->close();
?>
