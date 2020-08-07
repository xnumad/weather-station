-- MySQL dump 10.17  Distrib 10.3.15-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: weatherStation
-- ------------------------------------------------------
-- Server version	10.3.15-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `weatherStation`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `weatherStation` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `weatherStation`;

--
-- Table structure for table `groups`
--

DROP TABLE IF EXISTS `groups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `groups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text CHARACTER SET utf8mb4 NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `groups`
--

LOCK TABLES `groups` WRITE;
/*!40000 ALTER TABLE `groups` DISABLE KEYS */;
INSERT INTO `groups` VALUES (1,'Group name');
/*!40000 ALTER TABLE `groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `measurements`
--

DROP TABLE IF EXISTS `measurements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `measurements` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `station_id` int(11) unsigned NOT NULL COMMENT 'From which station the measurement originates',
  `time_measured` int(11) unsigned DEFAULT unix_timestamp(current_timestamp()) COMMENT 'When the measurement was taken (actually when it was received) in Unix time (UTC)',
  `temperature` decimal(10,0) NOT NULL COMMENT '°C',
  `humidity` decimal(10,2) DEFAULT NULL COMMENT 'g/m³',
  `relative_humidity` decimal(3,0) NOT NULL COMMENT '%H',
  PRIMARY KEY (`id`),
  KEY `FK_measurements_stations` (`station_id`),
  CONSTRAINT `FK_measurements_stations` FOREIGN KEY (`station_id`) REFERENCES `stations` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Contains all the weather measurements';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `measurements`
--

LOCK TABLES `measurements` WRITE;
/*!40000 ALTER TABLE `measurements` DISABLE KEYS */;
INSERT INTO `measurements` VALUES (1,1,0,26,13.66,56);
/*!40000 ALTER TABLE `measurements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `relative_humidity`
--

DROP TABLE IF EXISTS `relative_humidity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `relative_humidity` (
  `temperature` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '°C',
  `max_humidity` decimal(10,2) unsigned NOT NULL COMMENT 'g/m³',
  KEY `Schlüssel 1` (`temperature`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='values for calculation of relative humidity';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `relative_humidity`
--

LOCK TABLES `relative_humidity` WRITE;
/*!40000 ALTER TABLE `relative_humidity` DISABLE KEYS */;
INSERT INTO `relative_humidity` VALUES (0,4.84),(1,5.20),(2,5.60),(3,6.00),(4,6.40),(5,6.80),(6,7.30),(7,7.80),(8,8.30),(9,8.80),(10,9.40),(11,10.00),(12,10.70),(13,11.40),(14,12.10),(15,12.80),(16,13.60),(17,14.50),(18,15.40),(19,16.30),(20,17.30),(21,18.30),(22,19.40),(23,20.60),(24,21.80),(25,23.00),(26,24.40),(27,25.80),(28,27.20),(29,28.70),(30,30.30);
/*!40000 ALTER TABLE `relative_humidity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stations`
--

DROP TABLE IF EXISTS `stations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stations` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` tinytext CHARACTER SET latin1 NOT NULL,
  `location` tinytext CHARACTER SET latin1 DEFAULT NULL COMMENT 'address',
  `group` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_stations_groups` (`group`),
  CONSTRAINT `FK_stations_groups` FOREIGN KEY (`group`) REFERENCES `groups` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Contains all the weather stations';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stations`
--

LOCK TABLES `stations` WRITE;
/*!40000 ALTER TABLE `stations` DISABLE KEYS */;
INSERT INTO `stations` VALUES (1,'Living room','Wall Street 1',1);
/*!40000 ALTER TABLE `stations` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-06-14 14:27:47
