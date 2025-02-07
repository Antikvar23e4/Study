--2.	Создать базу данных SQLite, дополняющую вашу базу данных SQL Server по варианту.
CREATE TABLE Country (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL
);

CREATE TABLE Tour (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    country_id INTEGER NOT NULL,
    FOREIGN KEY (country_id) REFERENCES Country(id)
);

--3.	Добавить данные в базу данных SQLite.
INSERT INTO Country (id, name) 
VALUES 
(1, 'France'),
(2, 'Italy'),
(3, 'Spain'),
(4, 'Germany'),
(5, 'Japan'),
(6, 'India');


INSERT INTO Tour (id, name, country_id) 
VALUES 
(1, 'Paris City Tour', 1),
(2, 'Wine Tasting in Bordeaux', 1),
(3, 'Rome Historical Walk', 2),
(4, 'Venice Gondola Experience', 2),
(5, 'Barcelona Modernism', 3),
(6, 'Madrid Art and Culture', 3),
(7, 'Berlin Wall Exploration', 4),
(8, 'Munich Oktoberfest', 4),
(9, 'Kyoto Cherry Blossoms', 5),
(10, 'Tokyo Nightlife Adventure', 5),
(11, 'Taj Mahal Sunrise Visit', 6),
(12, 'Kerala Backwaters', 6);

SELECT * FROM Country;
SELECT * FROM Tour;

DELETE FROM Country;
DELETE FROM Tour;

--4.Продемонстрировать обновление, добавление и удаление данных в подчиненной таблице базы данных SQLite. 
--Обработка должна демонстрировать особенности применения внешних ключей в базе данных SQLite и использовать транзакции. 
--вкл внешн ключи
PRAGMA foreign_keys = ON;
--добавление
BEGIN TRANSACTION;
INSERT INTO Tour (id, name, country_id)
VALUES (14, 'Osaka Food Tour', 5);
COMMIT;

--обновление
UPDATE Tour
SET name = 'Paris Grand Tour'
WHERE id = 1;

--удаление
DELETE FROM Country WHERE id = 1; --FOREIGN KEY constraint failed (ограничение внешн ключа)

BEGIN TRANSACTION;
DELETE FROM Tour WHERE country_id = 1;
DELETE FROM Country WHERE id = 1;
COMMIT;

-- 5.	Создать представление в базе данных SQLite. 
CREATE VIEW TourDetails AS
SELECT 
    Tour.id AS tour_id,
    Tour.name AS tour_name,
    Country.name AS country_name
FROM 
    Tour
JOIN 
    Country ON Tour.country_id = Country.id;

SELECT * FROM TourDetails;
	
-- 6.	Создать необходимые индексы в базе данных SQLite.
CREATE INDEX idx_country_name ON Country(name);
PRAGMA index_list('Country');
SELECT * FROM Country WHERE name = 'Japan';
DROP INDEX idx_country_name;

-- 7.	Создать триггер в базе данных SQLite.
CREATE TRIGGER alert_on_delete
BEFORE DELETE ON Tour
BEGIN
    SELECT RAISE(ABORT, 'Удаление записи из таблицы Tour запрещено.');
END;
DELETE FROM Tour WHERE id = 14;
DROP TRIGGER alert_on_delete;


