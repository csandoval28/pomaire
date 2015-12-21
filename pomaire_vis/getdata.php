<script type="text/javascript">
window.onload = setupRefresh;

function setupRefresh() {
  setTimeout("refreshPage();", 1000);
}
function refreshPage() {
   window.location = location.href;
}
</script>
<?php
#Evita que salgan errores
    error_reporting(E_ALL ^ E_DEPRECATED);
#############################################

$id=$_GET["id"];

$host = "localhost";
$username = "cpy9075_tpacheco";
$password = "7657881";
$database = "cpy9075_littledevices";

  
    $server = mysql_connect($host, $username, $password);
    $connection = mysql_select_db($database, $server);

    $myquery = "
(SELECT * FROM sensores WHERE Latitud != '' AND id_nodo=$id ORDER BY id DESC LIMIT 1) ORDER BY id ASC	
    ";

    $query = mysql_query($myquery);

    if ( ! $myquery ) {
        echo mysql_error();
        die;
    }

    $data = array();

    for ($x = 0; $x < mysql_num_rows($query); $x++) {
        $data[] = mysql_fetch_assoc($query);
    }

    echo json_encode($data);     

    mysql_close($server);
?>