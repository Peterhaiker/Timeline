-- MySQL dump 10.13  Distrib 5.7.20, for Linux (i686)
--
-- Host: localhost    Database: timeline
-- ------------------------------------------------------
-- Server version	5.7.20-0ubuntu0.16.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `刘海亮_event`
--

DROP TABLE IF EXISTS `刘海亮_event`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `刘海亮_event` (
  `executor` varchar(20) NOT NULL,
  `event` varchar(200) NOT NULL,
  `exec_time` datetime NOT NULL,
  `state` varchar(5) DEFAULT '未完成'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `刘海亮_event`
--

LOCK TABLES `刘海亮_event` WRITE;
/*!40000 ALTER TABLE `刘海亮_event` DISABLE KEYS */;
INSERT INTO `刘海亮_event` VALUES ('刘海亮','完成timeline数据备份功能\n','2018-01-22 12:00:00','未完成');
/*!40000 ALTER TABLE `刘海亮_event` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `刘海亮_profile`
--

DROP TABLE IF EXISTS `刘海亮_profile`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `刘海亮_profile` (
  `account` varchar(20) NOT NULL,
  `sex` varchar(2) DEFAULT NULL,
  `birth` date DEFAULT NULL,
  `phone` varchar(14) DEFAULT NULL,
  `motto` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='刘海亮用户的好友列表';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `刘海亮_profile`
--

LOCK TABLES `刘海亮_profile` WRITE;
/*!40000 ALTER TABLE `刘海亮_profile` DISABLE KEYS */;
INSERT INTO `刘海亮_profile` VALUES ('刘海亮','男','1996-08-03','18593488685','不忘初心'),('李博',NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `刘海亮_profile` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `passwd`
--

DROP TABLE IF EXISTS `passwd`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `passwd` (
  `account` varchar(20) NOT NULL COMMENT '账户名',
  `passwd` varchar(50) NOT NULL,
  PRIMARY KEY (`account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `passwd`
--

LOCK TABLES `passwd` WRITE;
/*!40000 ALTER TABLE `passwd` DISABLE KEYS */;
INSERT INTO `passwd` VALUES ('刘海亮','*CC67043C7BCFF5EEA5566BD9B1F3C74FD9A5CF5D');
/*!40000 ALTER TABLE `passwd` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-01-22 11:10:17
