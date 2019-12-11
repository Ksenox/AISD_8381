use cw_db;


drop TABLE average_case;
drop TABLE worst_case;
drop TABLE all_tests;



-- ************************************** `all_tests`

CREATE TABLE `all_tests`
(
 `id`      int
(7) unsigned NOT NULL AUTO_INCREMENT ,
 `itemset` longtext NOT NULL ,
 `time`    float
(25,10) NOT NULL ,
 `time_2`    float
(25,10),
 `steps`   int
(7) unsigned NOT NULL,

PRIMARY KEY
(`id`)
);


-- ************************************** `worst_case`

CREATE TABLE `worst_case`
(
 `id`               int
(7) unsigned NOT NULL AUTO_INCREMENT ,
 `number_of_tests`  int
(6) NOT NULL ,
 `number_of_leaves` int
(7) NOT NULL ,
 `time`             float
(25,10) NOT NULL ,
 `time_2`             float
(25,10) NOT NULL ,
 `steps`   int
(7) unsigned NOT NULL,

PRIMARY KEY
(`id`)
);


-- ************************************** `average_case`

CREATE TABLE `average_case`
(
 `id`               int
(7) unsigned NOT NULL AUTO_INCREMENT ,
 `number_of_tests`  int
(6) NOT NULL ,
 `number_of_leaves` int
(7) NOT NULL ,
 `time`             float
(25,10) NOT NULL ,
 `time_2`             float
(25,10) NOT NULL ,
 `steps`   int
(7) unsigned NOT NULL,

PRIMARY KEY
(`id`)
);






