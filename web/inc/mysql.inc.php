<?php
define('DB_HOST', 				'localhost');
define('DB_USER', 				'root');
define('DB_PASS', 			    'baidu@123');
define('DB_NAME', 	  			'p2sp_stat');


class CMysql
{
	function __construct($dbHost, $dbUser, $dbPass, $dbName)
	{
		$this->m_dbConn = mysql_connect($dbHost, $dbUser, $dbPass);
/*
		$this->Query("set character_set_results=utf8");
		$this->Query("set character_set_client=utf8");
		$this->Query("set character_set_connection=utf8");
*/
		$this->Query("set names utf8");
		if (isset($dbName))
			mysql_select_db($dbName, $this->m_dbConn);
	}

	function __destruct()
	{
		mysql_close($this->m_dbConn);
	}

	function Query($sql)
	{
		$this->m_Result = mysql_query($sql, $this->m_dbConn);

		if (!$this->m_Result)
		{
			echo mysql_error($this->m_dbConn). "\n";
			exit(0);
		}
		return $this->m_Result;
	}

	function FetchArray()
	{
		return mysql_fetch_array($this->m_Result);
	}

	function GetFieldsNum()
	{
		return mysql_num_fields($this->m_Result);
	}
	
	function AffectedRows()
	{
		return mysql_affected_rows($this->m_dbConn);
	}
	
	function FetchField($i)
	{
		return mysql_fetch_field($this->m_Result, $i);
	}

	private $m_dbConn;
	private $m_Result;

};




function get_real_ip()
{
	$ip=false;
	if(!empty($_SERVER["HTTP_CLIENT_IP"]))
	{
		$ip = $_SERVER["HTTP_CLIENT_IP"];
	}

	if (!empty($_SERVER['HTTP_X_FORWARDED_FOR']))
	{
		$ips = explode (", ", $_SERVER['HTTP_X_FORWARDED_FOR']);
		if ($ip)
		{
			array_unshift($ips, $ip);
			$ip = FALSE;
		}

		for ($i = 0; $i < count($ips); $i++)
		{
			if (!eregi ("^(10|172\.16|192\.168)\.", $ips[$i]))
			{
				$ip = $ips[$i];
				break;
			}
		}
	}
	return ($ip ? $ip : $_SERVER['REMOTE_ADDR']);
}
?>

<?php   
class mysql
{  
	private $host;    //���ݿ�host  localhost
	private $name;    //���ݿ��û���
	private $pass;    //���ݿ�����
	private $table;    //��
	private $ut;    //���ݿ����
 
 function __construct($host,$name,$pass,$table,$ut)
 {
  $this->host = $host; //������host = ��������ֵ 
  $this->name = $name; //������name = ��������ֵ 
  $this->pass = $pass; //������pass = ��������ֵ 
  $this->table = $table; //������table = ��������ֵ 
  $this->ut = $ut;  //������ut = ��������ֵ 
  $this->connect();  //����connect���� �������ݿ�
 }
 
 function connect()
 {  
  $link=mysql_connect($this->host,$this->name,$this->pass) or die ($this->error()); //�������ݿ⺯��
  mysql_select_db($this->table,$link) or die("û�����ݿ⣺".$this->table);   //ѡ�����ݿ⺯��
  mysql_query("SET NAMES '$this->ut'");            //ѡ�����ݿ���뺯��         
 }
 
 function query($sql, $type = '') 
 { 
  if(!($query = mysql_query($sql))) $this->show('Say:', $sql);      //���ʧ�ܵ���show����
  return $query;                  //��������Դ
 }
 
 function show($message = '', $sql = '') 
 {       
  if(!$sql) echo $message;  else echo $message.'<br>'.$sql;       //��ѯ����
 }
 
 //---------------���º�������PHP�ֲ�
 function affected_rows() 
 { 
  return mysql_affected_rows();
 }
 function result($query, $row) 
 { 
  return mysql_result($query, $row);
 }
 function num_rows($query) 
 { 
  return @mysql_num_rows($query);
 }
 function num_fields($query) 
 {
  return mysql_num_fields($query);
 }
 function free_result($query) 
 {
  return mysql_free_result($query);
 }
 function insert_id() 
 { 
  return mysql_insert_id(); 
 }
 function fetch_row($query) 
 {  
  return mysql_fetch_row($query);
 }
 function version() 
 {
  return mysql_get_server_info();
 }
 function close() 
 {
  return mysql_close();
 } 
}
?> 
