CREATE DATABASE  IF NOT EXISTS `EGEInformatica` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci */;
USE `EGEInformatica`;
-- MySQL dump 10.13  Distrib 5.7.32, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: EGEInformatica
-- ------------------------------------------------------
-- Server version	5.7.32-0ubuntu0.18.04.1

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
-- Table structure for table `Вариант_задания`
--

DROP TABLE IF EXISTS `Вариант_задания`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Вариант_задания` (
  `idВариантзадания` int(11) NOT NULL AUTO_INCREMENT,
  `idТипзадания` int(11) NOT NULL,
  `Название` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`idВариантзадания`),
  KEY `fk_Вариант_задания_1_idx` (`idТипзадания`),
  CONSTRAINT `fk_Вариант_задания_1` FOREIGN KEY (`idТипзадания`) REFERENCES `Тип_задания` (`idТипзадания`)
) ENGINE=InnoDB AUTO_INCREMENT=92 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Вариант_задания`
--

LOCK TABLES `Вариант_задания` WRITE;
/*!40000 ALTER TABLE `Вариант_задания` DISABLE KEYS */;
INSERT INTO `Вариант_задания` VALUES (1,1,'Неоднозначное соотнесение таблицы и графа'),(2,1,'Однозначное соотнесение таблицы и графа'),(3,1,'Поиск оптимального маршрута по таблице'),(4,2,'Монотонные функции'),(5,2,'Немонотонные функции'),(6,2,'Строки с пропущенными значениями'),(7,2,'Разные задачи'),(8,3,'Поголовный пересчёт'),(9,3,'Родственные отношения, братья и сёстры'),(10,3,'Родственные отношения, дяди и тёти'),(11,3,'Определение данных по двум таблицам'),(12,3,'Определение данных по одной таблице'),(13,3,'Родственные отношения, племянники, племянницы, дедушки, внуки и внучки'),(14,4,'Выбор кода при неиспользуемых сигналах'),(15,4,'Шифрование по известному коду и перевод в различные СС'),(16,4,'Расшифровка сообщений'),(17,4,'Передача информации. Выбор кода'),(18,5,'Исполнители на плоскости'),(19,5,'Посимвольное двоичное преобразование'),(20,5,'Разные задачи'),(21,5,'Арифмометры'),(22,5,'Арифмометры с движением в обе стороны'),(23,5,'Посимвольное десятичное преобразование'),(24,6,'Две линейные функции'),(25,6,'Сумма двух линейных функций'),(26,6,'Арифметическая прогрессия'),(27,6,'Условие выполнения цикла while'),(28,7,'Передача звуковых файлов'),(29,7,'Передача изображений'),(30,7,'Передача текстовых файлов'),(31,7,'Хранение звуковых файлов'),(32,7,'Сравнение двух способов передачи данных'),(33,7,'Определение времени передачи файла'),(34,7,'Хранение изображений'),(35,7,'Определение размера записанного файла'),(36,8,'Подсчет количества слов'),(37,8,'Подсчет количества слов с ограничениями'),(38,8,'Последовательность лампочек'),(39,8,'Последовательность сигнальных ракет'),(40,8,'Разное'),(41,8,'Подсчет количества разных последовательностей'),(42,8,'Слова по порядку'),(43,9,'Разное'),(44,10,'Разное'),(45,11,'Пароли с дополнительными сведениями'),(46,11,'Разное'),(47,11,'Номера спортсменов'),(48,11,'Автомобильные номера'),(49,11,'Пароли'),(50,12,'Исполнитель Редактор'),(51,12,'Исполнитель Чертёжник'),(52,12,'Остановка в заданной клетке, циклы с оператором ПОКА'),(53,12,'Нестандартные задачи'),(54,12,'Остановка в заданной клетке, циклы с операторами ПОКА и ЕСЛИ'),(55,12,'Остановка в клетке, из которой начато движение'),(56,13,'Подсчёт путей с избегаемой вершиной'),(57,13,'Подсчёт путей с обязательной и избегаемой вершинами'),(58,13,'Подсчёт путей'),(59,13,'Подсчёт путей с обязательной вершиной'),(60,14,'Разное'),(61,14,'Прямое сложение в СС'),(62,14,'Определение основания'),(63,15,'Побитовая конъюнкция'),(64,15,'Числовая плоскость'),(65,15,'Множества'),(66,15,'Разное'),(67,16,'Программы с двумя рекурсивными функциями с возвращаемыми значениями'),(68,16,'Программы с двумя рекурсивными функциями с текстовым выводом'),(69,16,'Рекурсивные функции с возвращаемыми значениями'),(70,16,'Алгоритмы, опирающиеся на несколько предыдущих значений'),(71,16,'Рекурсивные функции с текстовым выводом'),(72,16,'Алгоритмы, опирающиеся на одно предыдущее значение'),(73,17,'Разное'),(74,18,'Разное'),(75,19,'Разное'),(76,20,'Разное'),(77,21,'Разное'),(78,22,'Посимвольная обработка восьмеричных чисел'),(79,22,'Посимвольная обработка чисел в разных СС'),(80,22,'Разное'),(81,22,'Посимвольная обработка десятичных чисел'),(82,23,'Количество программ'),(83,23,'Количество программ с обязательным этапом'),(84,23,'Количество программ с избегаемым этапом'),(85,23,'Количество программ с обязательным и избегаемым этапами'),(86,23,'Поиск количества программ по заданному числу'),(87,23,'Поиск количества чисел по заданному числу команд'),(88,24,'Разное'),(89,25,'Разное'),(90,26,'Разное'),(91,27,'Разное');
/*!40000 ALTER TABLE `Вариант_задания` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Вопрос`
--

DROP TABLE IF EXISTS `Вопрос`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Вопрос` (
  `idВопроса` int(11) NOT NULL AUTO_INCREMENT,
  `idВариантзадания` int(11) NOT NULL,
  `Название` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `Текст` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`idВопроса`),
  KEY `fk_Вопрос_1_idx` (`idВариантзадания`),
  CONSTRAINT `fk_Вопрос_1` FOREIGN KEY (`idВариантзадания`) REFERENCES `Вариант_задания` (`idВариантзадания`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Вопрос`
--

LOCK TABLES `Вопрос` WRITE;
/*!40000 ALTER TABLE `Вопрос` DISABLE KEYS */;
INSERT INTO `Вопрос` VALUES (1,36,'Первый вариант для задания №8','задание_8.1.1'),(2,36,'Второй вариант для задания №8','задание_8.1.2'),(3,36,'Третий вариант для задания №8','задание_8.1.3');
/*!40000 ALTER TABLE `Вопрос` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Задание`
--

DROP TABLE IF EXISTS `Задание`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Задание` (
  `idЗадания` int(11) NOT NULL AUTO_INCREMENT,
  `idВопроса` int(11) NOT NULL,
  `Название` varchar(70) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'Какое_то_заданий',
  `Правильный ответ` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `Текст` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `Макс.Балл` int(11) NOT NULL,
  PRIMARY KEY (`idЗадания`),
  KEY `fk_Задание_1_idx` (`idВопроса`),
  CONSTRAINT `fk_Задание_1` FOREIGN KEY (`idВопроса`) REFERENCES `Вопрос` (`idВопроса`)
) ENGINE=InnoDB AUTO_INCREMENT=590 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Задание`
--

LOCK TABLES `Задание` WRITE;
/*!40000 ALTER TABLE `Задание` DISABLE KEYS */;
INSERT INTO `Задание` VALUES (554,2,'Какое_то_заданий','243','<p id=\"text_of_ex811\">Сколько слов длины 5 можно составить из букв Е, Г, Э? Каждая буква может входить в слово несколько раз.</p>',1),(555,1,'Какое_то_заданий','3125','<p id=\"text_of_ex811\">Некоторый алфавит содержит 5 различных символов. Сколько 5 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(556,2,'Какое_то_заданий','81','<p id=\"text_of_ex811\">Сколько слов длины 4 можно составить из букв Е, Г, Э? Каждая буква может входить в слово несколько раз.</p>',1),(557,1,'Какое_то_заданий','27','<p id=\"text_of_ex811\">Некоторый алфавит содержит 3 различных символов. Сколько 3 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(558,1,'Какое_то_заданий','1024','<p id=\"text_of_ex811\">Некоторый алфавит содержит 4 различных символов. Сколько 5 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(559,1,'Какое_то_заданий','25','<p id=\"text_of_ex811\">Некоторый алфавит содержит 5 различных символов. Сколько 2 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(560,2,'Какое_то_заданий','3','<p id=\"text_of_ex811\">Сколько слов длины 1 можно составить из букв Е, Г, Э? Каждая буква может входить в слово несколько раз.</p>',1),(561,1,'Какое_то_заданий','256','<p id=\"text_of_ex811\">Некоторый алфавит содержит 4 различных символов. Сколько 4 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(562,1,'Какое_то_заданий','16','<p id=\"text_of_ex811\">Некоторый алфавит содержит 2 различных символов. Сколько 4 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(563,1,'Какое_то_заданий','81','<p id=\"text_of_ex811\">Некоторый алфавит содержит 3 различных символов. Сколько 4 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(564,1,'Какое_то_заданий','64','<p id=\"text_of_ex811\">Некоторый алфавит содержит 4 различных символов. Сколько 3 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(565,1,'Какое_то_заданий','243','<p id=\"text_of_ex811\">Некоторый алфавит содержит 3 различных символов. Сколько 5 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(566,2,'Какое_то_заданий','729','<p id=\"text_of_ex811\">Сколько слов длины 6 можно составить из букв Е, Г, Э? Каждая буква может входить в слово несколько раз.</p>',1),(567,1,'Какое_то_заданий','8','<p id=\"text_of_ex811\">Некоторый алфавит содержит 2 различных символов. Сколько 3 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(568,2,'Какое_то_заданий','27','<p id=\"text_of_ex811\">Сколько слов длины 3 можно составить из букв Е, Г, Э? Каждая буква может входить в слово несколько раз.</p>',1),(569,1,'Какое_то_заданий','16','<p id=\"text_of_ex811\">Некоторый алфавит содержит 4 различных символов. Сколько 2 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(570,1,'Какое_то_заданий','4','<p id=\"text_of_ex811\">Некоторый алфавит содержит 2 различных символов. Сколько 2 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(571,2,'Какое_то_заданий','9','<p id=\"text_of_ex811\">Сколько слов длины 2 можно составить из букв Е, Г, Э? Каждая буква может входить в слово несколько раз.</p>',1),(572,1,'Какое_то_заданий','125','<p id=\"text_of_ex811\">Некоторый алфавит содержит 5 различных символов. Сколько 3 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(573,1,'Какое_то_заданий','32','<p id=\"text_of_ex811\">Некоторый алфавит содержит 2 различных символов. Сколько 5 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(574,1,'Какое_то_заданий','9','<p id=\"text_of_ex811\">Некоторый алфавит содержит 3 различных символов. Сколько 2 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(575,1,'Какое_то_заданий','625','<p id=\"text_of_ex811\">Некоторый алфавит содержит 5 различных символов. Сколько 4 -буквенных слов можно составить из символов этого алфавита, если символы в слове могут повторяться?</p>',1),(576,3,'Какое_то_заданий','80','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 2 до 3 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(577,3,'Какое_то_заданий','128','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 3 до 3 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(578,3,'Какое_то_заданий','1280','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 4 до 5 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(579,3,'Какое_то_заданий','32','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 2 до 2 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(580,3,'Какое_то_заданий','2048','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 5 до 5 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(581,3,'Какое_то_заданий','1088','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 3 до 5 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(582,3,'Какое_то_заданий','4352','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 4 до 6 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(583,3,'Какое_то_заданий','320','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 3 до 4 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(584,3,'Какое_то_заданий','1040','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 2 до 5 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(585,3,'Какое_то_заданий','4112','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 2 до 6 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(586,3,'Какое_то_заданий','4160','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 3 до 6 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(587,3,'Какое_то_заданий','272','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 2 до 4 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(588,3,'Какое_то_заданий','512','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 4 до 4 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1),(589,3,'Какое_то_заданий','5120','<p id=\"text_of_ex811\">Сколько существует различных символьных последовательностей длины от 5 до 6 в четырёхбуквенном алфавите {A, T, Г, Ц}?</p>',1);
/*!40000 ALTER TABLE `Задание` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Класс`
--

DROP TABLE IF EXISTS `Класс`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Класс` (
  `idПреподавателя` int(11) NOT NULL,
  `idУченика` int(11) NOT NULL,
  `Статус` tinyint(4) NOT NULL,
  KEY `fk_Класс_1_idx` (`idПреподавателя`),
  KEY `fk_Класс_2_idx` (`idУченика`),
  CONSTRAINT `fk_Класс_1` FOREIGN KEY (`idПреподавателя`) REFERENCES `Преподаватель` (`idПреподавателя`),
  CONSTRAINT `fk_Класс_2` FOREIGN KEY (`idУченика`) REFERENCES `Ученик` (`idУченика`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Класс`
--

LOCK TABLES `Класс` WRITE;
/*!40000 ALTER TABLE `Класс` DISABLE KEYS */;
/*!40000 ALTER TABLE `Класс` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Преподаватель`
--

DROP TABLE IF EXISTS `Преподаватель`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Преподаватель` (
  `idПреподавателя` int(11) NOT NULL AUTO_INCREMENT,
  `Логин` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `Пароль` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `ФИО` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`idПреподавателя`,`Логин`),
  UNIQUE KEY `Пароль_UNIQUE` (`Пароль`),
  UNIQUE KEY `Логин_UNIQUE` (`Логин`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Преподаватель`
--

LOCK TABLES `Преподаватель` WRITE;
/*!40000 ALTER TABLE `Преподаватель` DISABLE KEYS */;
INSERT INTO `Преподаватель` VALUES (1,'Lantew','superpro','Лаптев Валерий Викторович'),(2,'Moroz','supercom','Морозов '),(3,'KurKur','supersql','Куркурин'),(4,'Tolas','superpuper','Толасова');
/*!40000 ALTER TABLE `Преподаватель` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Список_Заданий`
--

DROP TABLE IF EXISTS `Список_Заданий`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Список_Заданий` (
  `idТеста` int(11) NOT NULL,
  `idЗадания` int(11) NOT NULL,
  `Номер` int(11) NOT NULL,
  KEY `fk_Список_Заданий_1_idx` (`idТеста`),
  KEY `fk_Список_Заданий_2_idx` (`idЗадания`),
  CONSTRAINT `fk_Список_Заданий_1` FOREIGN KEY (`idТеста`) REFERENCES `Тест` (`idТеста`),
  CONSTRAINT `fk_Список_Заданий_2` FOREIGN KEY (`idЗадания`) REFERENCES `Задание` (`idЗадания`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Список_Заданий`
--

LOCK TABLES `Список_Заданий` WRITE;
/*!40000 ALTER TABLE `Список_Заданий` DISABLE KEYS */;
/*!40000 ALTER TABLE `Список_Заданий` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Статистика_по_заданиям`
--

DROP TABLE IF EXISTS `Статистика_по_заданиям`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Статистика_по_заданиям` (
  `idУченика` int(11) NOT NULL,
  `idЗадания` int(11) NOT NULL,
  `idТеста` int(11) NOT NULL,
  `Номер` int(11) DEFAULT NULL,
  `Балл` int(11) NOT NULL DEFAULT '0',
  `Ответ` varchar(70) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  KEY `fk_Статистика_по_заданиям_1_idx` (`idУченика`),
  KEY `fk_Статистика_по_заданиям_2_idx` (`idЗадания`),
  KEY `fk_Статистика_по_заданиям_3_idx` (`idТеста`),
  CONSTRAINT `fk_Статистика_по_заданиям_1` FOREIGN KEY (`idУченика`) REFERENCES `Ученик` (`idУченика`),
  CONSTRAINT `fk_Статистика_по_заданиям_2` FOREIGN KEY (`idЗадания`) REFERENCES `Задание` (`idЗадания`),
  CONSTRAINT `fk_Статистика_по_заданиям_3` FOREIGN KEY (`idТеста`) REFERENCES `Тест` (`idТеста`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Статистика_по_заданиям`
--

LOCK TABLES `Статистика_по_заданиям` WRITE;
/*!40000 ALTER TABLE `Статистика_по_заданиям` DISABLE KEYS */;
INSERT INTO `Статистика_по_заданиям` VALUES (1,554,223,1,1,'243'),(1,555,223,2,0,''),(1,556,223,3,1,'81'),(1,557,223,4,1,'27'),(1,558,223,5,1,'1024'),(1,556,224,2,0,''),(1,554,224,4,0,''),(1,559,224,1,0,''),(1,560,224,3,0,''),(1,561,224,5,0,''),(1,554,225,1,1,'243'),(1,562,225,2,1,'16'),(1,563,225,3,1,'81'),(1,564,225,4,0,'67'),(1,565,225,5,1,'243'),(1,560,226,2,0,'729'),(1,555,226,3,0,'3'),(1,561,226,4,0,'3125'),(1,566,226,1,0,'256'),(1,567,226,5,1,'8'),(1,558,227,1,1,'1024'),(1,560,227,5,0,'27'),(1,568,227,2,0,'16'),(1,569,227,3,0,'4'),(1,570,227,4,0,'3'),(1,556,228,2,0,'9'),(1,554,228,3,0,'81'),(1,566,228,4,0,'243'),(1,560,228,5,0,'729'),(1,571,228,1,0,'3'),(1,556,229,2,0,'125'),(1,568,229,3,0,'81'),(1,571,229,4,0,'27'),(1,562,229,5,0,'9'),(1,572,229,1,0,'16'),(1,556,230,1,1,'81'),(1,554,230,2,1,'243'),(1,560,230,3,1,'3'),(1,562,230,4,1,'16'),(1,568,230,5,1,'27'),(1,559,231,1,1,'25'),(1,556,231,2,1,'81'),(1,554,231,3,1,'243'),(1,571,231,4,1,'9'),(1,568,231,5,1,'27'),(1,572,232,1,1,'125'),(1,564,232,2,0,''),(1,560,232,3,1,'3'),(1,563,232,5,0,'32'),(1,573,232,4,0,'81'),(1,566,233,2,0,'9'),(1,554,233,3,0,''),(1,557,233,4,0,''),(1,574,233,1,0,'27'),(1,575,233,5,0,''),(1,574,234,1,1,'9'),(1,554,234,2,1,'243'),(1,571,234,3,1,'9'),(1,561,234,4,1,'256'),(1,556,234,5,1,'81'),(1,569,235,1,1,'16'),(1,560,235,2,1,'3'),(1,567,235,3,1,'8'),(1,575,235,4,0,''),(1,573,235,5,1,'32'),(1,564,236,1,0,''),(1,568,236,2,0,''),(1,563,236,3,0,''),(1,554,236,4,0,''),(1,565,236,5,0,''),(1,571,237,1,0,''),(1,566,237,2,0,''),(1,560,237,3,0,''),(1,565,237,4,0,''),(1,554,237,5,0,''),(1,555,238,1,1,'3125'),(1,571,238,2,1,'9'),(1,560,238,3,1,'3'),(1,563,238,4,1,'81'),(1,557,238,5,1,'27'),(1,566,239,2,1,'729'),(1,560,239,3,1,'3'),(1,554,239,4,1,'243'),(1,556,239,5,1,'81'),(1,576,239,1,1,'80'),(1,572,240,2,1,'125'),(1,571,240,4,1,'9'),(1,554,240,5,1,'243'),(1,577,240,1,1,'128'),(1,578,240,3,0,'1200'),(1,556,241,1,1,'81'),(1,564,241,3,1,'64'),(1,571,241,4,1,'9'),(1,579,241,2,1,'32'),(1,580,241,5,0,''),(1,568,242,1,0,''),(1,561,242,2,0,''),(1,571,242,4,0,''),(1,556,242,5,0,''),(1,581,242,3,0,''),(1,575,243,1,0,''),(1,580,243,2,0,''),(1,576,243,3,0,''),(1,568,243,4,0,''),(1,569,243,5,0,''),(1,578,244,1,0,''),(1,576,244,2,0,''),(1,557,244,3,0,''),(1,570,244,4,0,''),(1,582,244,5,0,''),(1,568,245,1,1,'27'),(1,560,245,2,1,'3'),(1,571,245,3,1,'9'),(1,554,245,4,1,'243'),(1,557,245,5,1,'27'),(1,566,245,6,0,''),(1,580,245,7,0,''),(1,562,246,1,1,'16'),(1,560,246,2,1,'3'),(1,566,246,5,1,'729'),(1,570,246,6,0,''),(1,578,246,7,0,''),(1,583,246,3,1,'320'),(1,584,246,4,1,'1040'),(1,570,247,1,1,'4'),(1,571,247,4,1,'9'),(1,562,247,7,1,'16'),(1,580,247,8,1,'2048'),(1,585,247,2,0,'4000'),(1,586,247,3,0,'4000'),(1,587,247,5,1,'272'),(1,588,247,6,1,'512'),(1,575,248,1,1,'625'),(1,559,248,2,1,'25'),(1,556,248,3,1,'81'),(1,571,248,4,1,'9'),(1,574,248,5,1,'9'),(1,579,248,7,1,'32'),(1,587,248,8,1,'272'),(1,564,248,9,1,'64'),(1,570,248,10,1,'4'),(1,589,248,6,0,'5100');
/*!40000 ALTER TABLE `Статистика_по_заданиям` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Статистика_по_тесту`
--

DROP TABLE IF EXISTS `Статистика_по_тесту`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Статистика_по_тесту` (
  `idУченика` int(11) NOT NULL,
  `idТеста` int(11) NOT NULL,
  `Балл` int(11) NOT NULL DEFAULT '0',
  KEY `fk_Статистика_по_тесту_1_idx` (`idУченика`),
  KEY `fk_Статистика_по_тесту_2_idx` (`idТеста`),
  CONSTRAINT `fk_Статистика_по_тесту_1` FOREIGN KEY (`idУченика`) REFERENCES `Ученик` (`idУченика`),
  CONSTRAINT `fk_Статистика_по_тесту_2` FOREIGN KEY (`idТеста`) REFERENCES `Тест` (`idТеста`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Статистика_по_тесту`
--

LOCK TABLES `Статистика_по_тесту` WRITE;
/*!40000 ALTER TABLE `Статистика_по_тесту` DISABLE KEYS */;
INSERT INTO `Статистика_по_тесту` VALUES (1,223,4),(1,224,0),(1,225,4),(1,226,1),(1,227,1),(1,228,0),(1,229,0),(1,230,5),(1,231,5),(1,232,2),(1,233,0),(1,234,5),(1,235,4),(1,236,0),(1,237,0),(1,238,5),(1,239,5),(1,240,4),(1,241,4),(1,242,0),(1,243,0),(1,244,0),(1,245,5),(1,246,5),(1,247,6),(1,248,9);
/*!40000 ALTER TABLE `Статистика_по_тесту` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Тест`
--

DROP TABLE IF EXISTS `Тест`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Тест` (
  `idТеста` int(11) NOT NULL AUTO_INCREMENT,
  `Кол_во_заданий` int(11) NOT NULL DEFAULT '1',
  `Макс.балл` int(11) NOT NULL DEFAULT '0',
  `idСтатуса` int(11) NOT NULL,
  `idСоздателя` int(11) NOT NULL,
  PRIMARY KEY (`idТеста`),
  KEY `fk_Тест_1_idx` (`idСтатуса`),
  KEY `fk_Тест_2_idx` (`idСоздателя`),
  CONSTRAINT `fk_Тест_1` FOREIGN KEY (`idСтатуса`) REFERENCES `статус` (`idСтатуса`),
  CONSTRAINT `fk_Тест_2` FOREIGN KEY (`idСоздателя`) REFERENCES `Ученик` (`idУченика`),
  CONSTRAINT `fk_Тест_3` FOREIGN KEY (`idСоздателя`) REFERENCES `Преподаватель` (`idПреподавателя`)
) ENGINE=InnoDB AUTO_INCREMENT=249 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Тест`
--

LOCK TABLES `Тест` WRITE;
/*!40000 ALTER TABLE `Тест` DISABLE KEYS */;
INSERT INTO `Тест` VALUES (223,5,5,1,1),(224,5,5,1,1),(225,5,5,1,1),(226,5,5,1,1),(227,5,5,1,1),(228,5,5,1,1),(229,5,5,1,1),(230,5,5,1,1),(231,5,5,1,1),(232,5,5,1,1),(233,5,5,1,1),(234,5,5,1,1),(235,5,5,1,1),(236,5,5,1,1),(237,5,5,1,1),(238,5,5,1,1),(239,5,5,1,1),(240,5,5,1,1),(241,5,5,1,1),(242,5,5,1,1),(243,5,5,1,1),(244,5,5,1,1),(245,7,7,1,1),(246,7,7,1,1),(247,8,8,1,1),(248,10,10,1,1);
/*!40000 ALTER TABLE `Тест` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Тип_задания`
--

DROP TABLE IF EXISTS `Тип_задания`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Тип_задания` (
  `idТипзадания` int(11) NOT NULL AUTO_INCREMENT,
  `Название` varchar(75) COLLATE utf8_unicode_ci NOT NULL,
  `Макс.Балл` int(11) NOT NULL,
  `Теория` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`idТипзадания`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Тип_задания`
--

LOCK TABLES `Тип_задания` WRITE;
/*!40000 ALTER TABLE `Тип_задания` DISABLE KEYS */;
INSERT INTO `Тип_задания` VALUES (1,'1. Анализ информационных моделей',1,''),(2,'2. Построение таблиц истинности логических выражений',1,''),(3,'3. Базы данных. Файловая система',1,''),(4,'4. Кодирование и декодирование информации',1,''),(5,'5. Анализ и построение алгоритмов для исполнителей',1,''),(6,'6. Анализ программ',1,''),(7,'7. Кодирование и декодирование информации. Передача информации',1,''),(8,'8. Перебор слов и системы счисления',1,'задание_8.html'),(9,'9. Эксель',1,''),(10,'10. Поиск символов в текстовом редакторе просмотреть',1,''),(11,'11. Вычисление количества информации',1,''),(12,'12. Выполнение алгоритмов для исполнителей',1,''),(13,'13. Поиск путей в графе',1,''),(14,'14. Кодирование чисел. Системы счисления',1,''),(15,'15. Преобразование логических выражений',1,''),(16,'16. Рекурсивные алгоритмы',1,''),(17,'17. Проверка на делимость',1,''),(18,'18. Робот-сборщик монет',1,''),(19,'19. Выигрышная стратегия. Задание 1',1,''),(20,'20. Выигрышная стратегия. Задание 2',1,''),(21,'21. Выигрышная стратегия. Задание 3',1,''),(22,'22. Анализ программы с циклами и условными операторами',1,''),(23,'23. Оператор присваивания и ветвления. Перебор вариантов, построение дерева',1,''),(24,'24. Обработка символьных строк',1,''),(25,'25. Обработка целочисленной информации',2,''),(26,'26. Обработка целочисленной информации',2,''),(27,'27. Программирование',2,'');
/*!40000 ALTER TABLE `Тип_задания` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Ученик`
--

DROP TABLE IF EXISTS `Ученик`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Ученик` (
  `idУченика` int(11) NOT NULL AUTO_INCREMENT,
  `Логин` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `Пароль` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `ФИО` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `Кол_во_тестов` int(11) DEFAULT NULL,
  `Кол_во_пропущенных_тестов` int(11) DEFAULT NULL,
  `Кол-во_тестов _после_теории` int(11) DEFAULT NULL,
  `Кол_во_вариантов` int(11) DEFAULT NULL,
  `Макс.балл_за_вариаты` int(11) DEFAULT NULL,
  `Мин.балл_за_вариаты` int(11) DEFAULT NULL,
  `Сред.балл_за_вариаты` int(11) DEFAULT NULL,
  `Макс.балл_за_случайный_вариант` int(11) DEFAULT NULL,
  `Кол_во_случайных_вариантов` int(11) DEFAULT NULL,
  `Мин_балл_за_случайный вариант` int(11) DEFAULT NULL,
  `Сред.балл_за_случайный_вариант` int(11) DEFAULT NULL,
  `Кол_во_вариантов_от_составителя` int(11) DEFAULT NULL,
  `Макс.балл_за_вариант_от_составителя` int(11) DEFAULT NULL,
  `Мин.балл_за_вариант_от_составителя` int(11) DEFAULT NULL,
  `Сред.балл_за_вариант_от_составителя` int(11) DEFAULT NULL,
  `Кол_во_вариантов_от_преподавателя` int(11) DEFAULT NULL,
  `Макс.балл_за_вариант_от_преподавателя` int(11) DEFAULT NULL,
  `Мин.балл_за_вариант_от_преподавателя` int(11) DEFAULT NULL,
  `Сред.балл_за_вариант_от_преподавателя` int(11) DEFAULT NULL,
  PRIMARY KEY (`idУченика`,`Логин`),
  UNIQUE KEY `Пароль_UNIQUE` (`Пароль`),
  UNIQUE KEY `Логин_UNIQUE` (`Логин`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ученик`
--

LOCK TABLES `Ученик` WRITE;
/*!40000 ALTER TABLE `Ученик` DISABLE KEYS */;
INSERT INTO `Ученик` VALUES (1,'Azaza','megaman','Азамат',26,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),(2,'Kusnez','megatop','Евгений',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),(3,'Amin','megalol','Амин',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
/*!40000 ALTER TABLE `Ученик` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `статус`
--

DROP TABLE IF EXISTS `статус`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `статус` (
  `idСтатуса` int(11) NOT NULL AUTO_INCREMENT,
  `Название` varchar(45) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`idСтатуса`),
  UNIQUE KEY `Название_UNIQUE` (`Название`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `статус`
--

LOCK TABLES `статус` WRITE;
/*!40000 ALTER TABLE `статус` DISABLE KEYS */;
INSERT INTO `статус` VALUES (3,'Варинта'),(2,'Теория'),(1,'Учебная');
/*!40000 ALTER TABLE `статус` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'EGEInformatica'
--

--
-- Dumping routines for database 'EGEInformatica'
--
/*!50003 DROP PROCEDURE IF EXISTS `checkApprentece` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `checkApprentece`(IN `log` varchar(70), IN `pas` varchar(70))
BEGIN
	select `Логин` from `Ученик` where `Логин` = `log` and `Пароль` = `pas`;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `checkTeacher` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `checkTeacher`(IN `log` varchar(70), IN `pas` varchar(70))
BEGIN
	select `Логин` from `Преподаватель` where `Логин` = `log` and `Пароль` = `pas`;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `check_for_skip` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `check_for_skip`(IN `log` varchar(70), IN `idt` int)
BEGIN

    declare is_prop varchar(70);
    set is_prop = (select GROUP_CONCAT(`Ответ` SEPARATOR '') from `Статистика_по_заданиям` where `idТеста` = `idt`);
    
    if (is_prop = '') then
		UPDATE `Ученик` SET `Кол_во_пропущенных_тестов` = `Кол_во_пропущенных_тестов`+1  WHERE `Логин` = `log`;
    end if;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `create_test` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `create_test`(IN `log` varchar(70), IN `N` int)
BEGIN
	declare id int;
	Set id = (select `idУченика` from `Ученик` where `Логин` = `log`);

	INSERT `Тест` (`idСоздателя`, `idСтатуса`, `Кол_во_заданий`) 
	VALUES (id, 1, `N`);
    
	INSERT `Статистика_по_тесту` (`idУченика`, `idТеста`) 
	VALUES ((select `idУченика` from `Ученик` where `Логин` = `log`), (select `idТеста` FROM `Тест` WHERE `idТеста`=LAST_INSERT_ID()));
    
    UPDATE `Ученик` SET `Кол_во_тестов` = `Кол_во_тестов`+1  WHERE `Логин` = `log`;

    select `idТеста` FROM `Тест` WHERE `idТеста`=LAST_INSERT_ID();
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `getMainStat` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `getMainStat`(IN `log` varchar(70))
BEGIN
	declare id int;
	declare kol int;
	Set id = (select `idУченика` from `Ученик` where `Логин` = `log`);
	Set kol = (select `Кол_во_тестов` from `Ученик` where `Логин` = `log`);

    select MAX(`Балл`), MIN(`Балл`), SUM(`Балл`)/kol FROM `Статистика_по_тесту` WHERE `idУченика`=id;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `getStatTest` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `getStatTest`(IN `log` varchar(70))
BEGIN
    
	select a.`idТеста`, a.`Балл`, b.`Макс.Балл` from `Статистика_по_тесту` a, `Тест` b where `idУченика` =  (select `idУченика` from `Ученик` where `Логин` = `log`) AND a.`idТеста` = b.`idТеста`;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `get_right_ans` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `get_right_ans`(IN `idt` int)
BEGIN

	select a.`idЗадания`, b.`Правильный ответ` from `Статистика_по_заданиям` a, `Задание` b where a.`idТеста` = `idt` AND a.`idЗадания` = b.`idЗадания` ORDER BY `Номер`;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `include_ex_to_test` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `include_ex_to_test`(IN `log` varchar(70), IN `idt` int, IN `idex` int, IN `num` int)
BEGIN

    INSERT `Статистика_по_заданиям`(`idУченика`, `idЗадания`, `idТеста`, `Номер`)
	VALUES ((select `idУченика` from `Ученик` where `Логин` = `log`), `idex`, `idt`, num);
    
    UPDATE `Тест` SET `Макс.Балл` = `Макс.Балл`+(select `Макс.Балл` from `Задание` where `idЗадания` = `idex`) WHERE `idТеста` = `idt`;

END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `set_ball_for_ex` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `set_ball_for_ex`(IN `log` varchar(70), IN `idt` int, IN `idex` int, IN `ans` varchar(70), IN `b` int)
BEGIN

    UPDATE `Статистика_по_заданиям`SET `Балл` = `b`, `Ответ` = replace(`ans`, ' ', '') WHERE `idТеста` = `idt` AND `idЗадания` = `idex` AND `idУченика` = (select `idУченика` from `Ученик` where `Логин` = `log`);
    
	UPDATE `Статистика_по_тесту` SET `Балл` = `Балл`+`b` WHERE `idТеста` = `idt`;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `set_ball_to_ex` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `set_ball_to_ex`(IN `log` varchar(70), IN `idex` int, IN `ans` varchar(70), IN `b` int)
BEGIN
    INSERT `Статистика_по_заданиям`(`idУченика`, `idЗадания`, `Балл`, `Ответ`)
	VALUES ((select `idУченика` from `Ученик` where `Логин` = `log`), `idex`, `b`, replace(`ans`, ' ', ''));
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `set_ball_to_test` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `set_ball_to_test`(IN `log` varchar(70), IN `idt` int)
BEGIN

    declare is_prop varchar(70);
    declare ball int;
	set ball = (select SUM(`Балл`) from `Статистика_по_заданиям` where `idЗадания` IN (select `idЗадания` from `Список_Заданий` where `idТеста` = `idt`));
    
    set is_prop = (select GROUP_CONCAT(`Ответ` SEPARATOR '') from `Статистика_по_заданиям` where `idЗадания` IN (select `idЗадания` from `Список_Заданий` where `idТеста` = `idt`));
    
	INSERT `Статистика_по_тесту` (`idУченика`, `idТеста`, `Балл`) 
	VALUES ((select `idУченика` from `Ученик` where `Логин` = `log`), `idt`, ball);
    
    if (is_prop = '') then
		UPDATE `Ученик` SET `Кол_во_пропущенных_тестов` = `Кол_во_пропущенных_тестов`+1  WHERE `Логин` = `log`;
    end if;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `update_exersize` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`user`@`localhost` PROCEDURE `update_exersize`(IN `idv` int, IN `text` varchar(200), IN `ans` varchar(70))
BEGIN

	INSERT `Задание` (`idВопроса`, `Текст`, `Правильный ответ`, `Макс.Балл`)
	VALUES (`idv`, `text`, `ans`, (select `Макс.Балл` from `Тип_задания` where `idТипзадания` = (select `idТипзадания` from `Вариант_задания` where `idВариантзадания` = (select `idВариантзадания` from `Вопрос` where `idВопроса` = 1))));

    select `idЗадания` FROM `Задание` WHERE `idЗадания`=LAST_INSERT_ID();
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-01-03 11:36:48
