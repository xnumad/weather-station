<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <link rel="stylesheet" href="https://unpkg.com/purecss@1.0.0/build/pure-min.css" integrity="sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w" crossorigin="anonymous">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Arduino Weather Station</title>
</head>
<body>
  <a href="/" style="text-decoration:none"><h1>Arduino Weather Station</h1></a>
  <h2>Select a <i>station</i> or <i>group</i> to see its measurements.</h2>

  <h3>Groups</h3>
  <table class="pure-table">
    <thead>
      <tr>
        <th>ID</th>
        <th>Name</th>
        <th>Member stations</th>
        <th>Measurements</th>
      </tr>
    </thead>

    <tbody>
      <?php
      $mysqli = new mysqli("localhost", "root", 'pw', "weatherStation");
      $sql = "SELECT * FROM groups;";
      $statement = $mysqli->prepare($sql);
      $statement->execute();
      $result = $statement->get_result();

      while($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<td>".$row["id"]."</td>";
        echo "<td><a href=\"/view_group.php?id=".$row["id"]."\">".$row["name"]."</a></td>";

        $sql = "SELECT COUNT(*) AS members FROM stations WHERE `group` = ".$row["id"];
        $statement = $mysqli->prepare($sql);
        $statement->execute();
        $members_amount_row = $statement->get_result()->fetch_assoc();
        echo "<td>".$members_amount_row["members"]."</td>";

        $sql = "SELECT COUNT(*) AS measurements FROM measurements WHERE station_id = ANY (SELECT id FROM stations	WHERE `group` = ".$row["id"].")";
        $statement = $mysqli->prepare($sql);
        $statement->execute();
        $measurements_amount_row = $statement->get_result()->fetch_assoc();
        echo "<td>".$measurements_amount_row["measurements"]."</td>";

        echo "</tr>";
      }
      ?>
    </tbody>
  </table>

  <h3>Stations</h3>
  <table class="pure-table">
    <thead>
      <tr>
        <th>ID</th>
        <th>Name</th>
        <th>Location</th>
        <th>Measurements</th>
        <th>Group</th>
      </tr>
    </thead>

    <tbody>
      <?php
      $sql = "SELECT * FROM stations;";
      $statement = $mysqli->prepare($sql);
      $statement->execute();
      $result = $statement->get_result();

      while($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<td>".$row["id"]."</td>";
        echo "<td><a href=\"/view_station.php?id=".$row["id"]."\">".$row["name"]."</a></td>";
        echo "<td>".$row["location"]."</td>";

        $sql = "SELECT COUNT(*) AS measurements FROM measurements WHERE station_id = ".$row["id"];
        $statement = $mysqli->prepare($sql);
        $statement->execute();
        $measurements_amount_row = $statement->get_result()->fetch_assoc();
        echo "<td>".$measurements_amount_row["measurements"]."</td>";

        echo "<td><a href=\"/view_group.php?id=".$row["id"]."\">".$row["group"]."</a></td>";
        echo "</tr>";
      }
      ?>
    </tbody>
  </table>

  <style>
  .footer {
    position: fixed;
    left: 0;
    bottom: 0;
    width: 100%;
    text-align: right;
  }
  </style>
  <div class="footer">
    <a href="https://www.iconfinder.com/icons/118959/clear_weather_icon">Favicon source</a>
  </div>
</body>
</html>
