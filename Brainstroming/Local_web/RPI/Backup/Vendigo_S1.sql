-- phpMyAdmin SQL Dump
-- version 5.0.4deb2+deb11u1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Oct 29, 2022 at 10:08 AM
-- Server version: 10.5.15-MariaDB-0+deb11u1
-- PHP Version: 7.4.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `Vendigo_S1`
--

-- --------------------------------------------------------

--
-- Table structure for table `BoxCondition`
--

CREATE TABLE `BoxCondition` (
  `RefID` int(11) NOT NULL,
  `BoxNumber` varchar(2) COLLATE utf8_unicode_ci NOT NULL,
  `BoxCondition` varchar(3) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `BoxCondition`
--

INSERT INTO `BoxCondition` (`RefID`, `BoxNumber`, `BoxCondition`) VALUES
(1, '1', 'on'),
(2, '2', 'on'),
(3, '3', 'on'),
(4, '4', 'on'),
(5, '5', 'on'),
(6, '6', 'on'),
(7, '7', 'on'),
(8, '8', 'on'),
(9, '9', 'on'),
(10, '10', 'on');

-- --------------------------------------------------------

--
-- Table structure for table `BoxDescription`
--

CREATE TABLE `BoxDescription` (
  `RefID` int(11) NOT NULL,
  `BoxNumber` varchar(2) COLLATE utf8_unicode_ci NOT NULL,
  `BoxDescription` varchar(255) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `BoxDescription`
--

INSERT INTO `BoxDescription` (`RefID`, `BoxNumber`, `BoxDescription`) VALUES
(1, '1', 'Food'),
(2, '2', 'Food'),
(3, '3', 'Food'),
(4, '4', 'Food'),
(5, '5', 'Food'),
(6, '6', 'Food'),
(7, '7', 'Food'),
(8, '8', 'Food'),
(9, '9', 'Food'),
(10, '10', 'Courier');

-- --------------------------------------------------------

--
-- Table structure for table `BoxStatus`
--

CREATE TABLE `BoxStatus` (
  `RefID` int(11) NOT NULL,
  `BoxNumber` varchar(2) COLLATE utf8_unicode_ci NOT NULL,
  `BoxStatus` varchar(1) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `BoxStatus`
--

INSERT INTO `BoxStatus` (`RefID`, `BoxNumber`, `BoxStatus`) VALUES
(1, '1', '1'),
(2, '2', '0'),
(3, '3', '0'),
(4, '4', '0'),
(5, '5', '0'),
(6, '6', '0'),
(7, '7', '0'),
(8, '8', '0'),
(9, '9', '0'),
(10, '10', '1');

-- --------------------------------------------------------

--
-- Table structure for table `OrderHistory`
--

CREATE TABLE `OrderHistory` (
  `RefID` int(11) NOT NULL,
  `Name` text NOT NULL,
  `OrderNumber` varchar(6) NOT NULL,
  `PhoneNumber` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `OrderHistory`
--

INSERT INTO `OrderHistory` (`RefID`, `Name`, `OrderNumber`, `PhoneNumber`) VALUES
(1, 'Abhishek', '11001', '9999999999'),
(2, 'Abhishek', '11002', '9999999999'),
(3, 'Abhishek', '11003', '9999999999'),
(4, 'Abhishek', '11004', '9999999999'),
(5, 'Abhishek', '11005', '9999999999'),
(6, 'Abhishek', '11006', '9999999999'),
(7, 'Abhishek', '11007', '9999999999'),
(8, 'Abhishek', '11008', '9999999999'),
(9, 'Abhishek', '11009', '9999999999'),
(10, 'Abhishek', '11010', '9999999999');

-- --------------------------------------------------------

--
-- Table structure for table `orders`
--

CREATE TABLE `orders` (
  `RefID` int(11) NOT NULL,
  `OrderNumber` varchar(6) NOT NULL,
  `BoxNumber` varchar(2) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `OTP` int(6) NOT NULL,
  `PhoneNumber` varchar(10) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `orders`
--

INSERT INTO `orders` (`RefID`, `OrderNumber`, `BoxNumber`, `OTP`, `PhoneNumber`) VALUES
(1, '11001', '1', 536852, '9999999999'),
(2, '11002', '2', 657893, '9999999999'),
(3, '11003', '3', 342567, '9999999999'),
(4, '11004', '4', 987234, '8888888888'),
(5, '11005', '5', 546476, '9999999999'),
(6, '11006', '6', 564754, '8888888888'),
(7, '11007', '7', 556366, '9999999999'),
(8, '11008', '8', 645254, '8888888888'),
(9, '11009', '9', 578761, '9999999999'),
(10, '11020', '10', 325657, '8888888888');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `userID` int(11) NOT NULL,
  `username` varchar(28) COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(64) COLLATE utf8_unicode_ci NOT NULL,
  `salt` varchar(8) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`userID`, `username`, `password`, `salt`) VALUES
(1, 'admin', '6502398e8233353625aad66ed8791bf99902477348af78f08464b106e3a4bf41', '119e368b');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `BoxCondition`
--
ALTER TABLE `BoxCondition`
  ADD PRIMARY KEY (`RefID`),
  ADD UNIQUE KEY `BoxNumber` (`BoxNumber`) USING BTREE;

--
-- Indexes for table `BoxDescription`
--
ALTER TABLE `BoxDescription`
  ADD PRIMARY KEY (`RefID`),
  ADD UNIQUE KEY `BoxNumber` (`BoxNumber`) USING BTREE;

--
-- Indexes for table `BoxStatus`
--
ALTER TABLE `BoxStatus`
  ADD PRIMARY KEY (`RefID`),
  ADD UNIQUE KEY `BoxNumber` (`BoxNumber`) USING BTREE;

--
-- Indexes for table `OrderHistory`
--
ALTER TABLE `OrderHistory`
  ADD PRIMARY KEY (`RefID`);

--
-- Indexes for table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`RefID`),
  ADD UNIQUE KEY `BoxNumber` (`BoxNumber`),
  ADD UNIQUE KEY `OrderNumber` (`OrderNumber`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`userID`),
  ADD UNIQUE KEY `username` (`username`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `BoxCondition`
--
ALTER TABLE `BoxCondition`
  MODIFY `RefID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `BoxDescription`
--
ALTER TABLE `BoxDescription`
  MODIFY `RefID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `BoxStatus`
--
ALTER TABLE `BoxStatus`
  MODIFY `RefID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `OrderHistory`
--
ALTER TABLE `OrderHistory`
  MODIFY `RefID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `orders`
--
ALTER TABLE `orders`
  MODIFY `RefID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `userID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
