/*1*/
--Определить все индексы, которые имеются в БД UNIVER. 
USE UNIVER;
EXEC SP_HELPINDEX 'AUDITORIUM_TYPE' 

CREATE TABLE #TASK1
(
    Nomer INT,
    Stroka NVARCHAR(20)
);

SET NOCOUNT ON;

DECLARE @I INT = 0;
WHILE @I < 1000
BEGIN
    INSERT #TASK1(Nomer, Stroka) VALUES (FLOOR(20000*RAND()), REPLICATE('СООБЩЕНИЕ', 2));
    IF (@I % 100 = 0) PRINT @I;
    SET @I = @I + 1;
END;
--Разработать SELECT-запрос. По-лучить план запроса и определить его стоимость
SELECT * FROM #TASK1 WHERE Nomer BETWEEN 1000 AND 1500 ORDER BY Nomer;

-- Получение плана выполнения
SET SHOWPLAN_TEXT ON;
GO
SELECT * FROM #TASK1 WHERE Nomer BETWEEN 1000 AND 1500 ORDER BY Nomer;
GO
SET SHOWPLAN_TEXT OFF;
--Создать кластеризованный индекс, уменьшающий стоимость SELECT-запроса.
CREATE CLUSTERED INDEX #TASK1_CL ON #TASK1(Nomer ASC);
SELECT * FROM #TASK1 WHERE Nomer BETWEEN 1500 AND 2500 ORDER BY Nomer

DROP INDEX #TASK1_CL ON #TASK1
DROP TABLE #TASK1
/*2*/
CREATE TABLE #TASK2
(
    Stroka NVARCHAR(20),
    Iterator INT IDENTITY(1,1),
    Nomer INT 
)
DECLARE @X INT = 0;
WHILE @X <= 10000
BEGIN
    INSERT INTO #TASK2(Stroka, Nomer)
    VALUES ('СООБЩЕНИЕ' + CAST(@X AS NVARCHAR), FLOOR(20000 * RAND()))
    SET @X += 1;
END
--Разработать SELECT-запрос. По-лучить план запроса и определить его стоимость. 
SELECT * FROM #TASK2 WHERE Stroka = 'СООБЩЕНИЕ2' AND Nomer >= 1000

CHECKPOINT;
DBCC DROPCLEANBUFFERS

--Создать некластеризованный не-уникальный составной индекс. 
CREATE INDEX #TASK2_NONCL ON #TASK2(Stroka, Nomer)
--Оценить процедуры поиска ин-формации.
SELECT * FROM #TASK2 WHERE Stroka = 'СООБЩЕНИЕ2' AND Nomer >= 1000

DROP INDEX #TASK2_NONCL ON #TASK2
DROP TABLE #TASK2
/*3*/
CREATE TABLE #TASK3
(
Stroka NVARCHAR (20),
Iterator INT IDENTITY(1,1),
Nomer INT 
)
DECLARE @H INT =0;
WHILE @H <= 10000
BEGIN
INSERT INTO #TASK3(Stroka,Nomer)
VALUES ('СООБЩЕНИЕ' + CAST(@H AS NVARCHAR),FLOOR(20000*RAND()))
SET @H +=1;
END
--Разработать SELECT-запрос. По-лучить план запроса и определить его стоимость. 
SELECT Stroka FROM #TASK3 WHERE Iterator <= 10000 
--Создать некластеризованный ин-декс покрытия, уменьшающий сто-имость SELECT-запроса. 
CREATE INDEX #NONCLASSIND ON #TASK3 (Iterator) INCLUDE (Stroka)
SELECT Stroka FROM #TASK3 WHERE Iterator = 666

DROP INDEX #NONCLASSIND ON #TASK3
DROP TABLE #TASK3
/*4*/
CREATE TABLE #TASK4
(
Stroka NVARCHAR (20),
Iterator INT IDENTITY(1,1),
Nomer INT 
)

DECLARE @M INT =0;
WHILE @M <= 10000
BEGIN
INSERT INTO #TASK4(Stroka,Nomer)
VALUES ('СООБЩЕНИЕ' + CAST(@M AS NVARCHAR),FLOOR(20000*RAND()))
SET @M +=1;
END
--Разработать SELECT-запрос, по-лучить план запроса и определить его стоимость. 
SELECT Iterator FROM #TASK4 
WHERE Iterator > 666 AND Iterator < 2000
--Создать некластеризованный фильтруемый индекс, уменьшающий стоимость SELECT-запроса
CREATE INDEX #NONCLASSFILTR ON #TASK4(Iterator)
WHERE (Iterator > 1500 AND Iterator < 2000)

CHECKPOINT;--используется для высвобождения накопленных изменений из буферного кэша на диск.
DBCC DROPCLEANBUFFERS--используется для очистки буферного кэша SQL Server.

SELECT Iterator FROM #TASK4 
WHERE Iterator > 666 AND Iterator < 2000

DROP INDEX #NONCLASSFILTR ON #TASK4
/*5*/
CREATE TABLE #TASK5
(
Stroka NVARCHAR (20),
Iterator INT IDENTITY(1,1),
Nomer INT 
)

DECLARE @L INT =0;
WHILE @L <= 10000
BEGIN
INSERT INTO #TASK5(Stroka,Nomer)
VALUES ('СООБЩЕНИЕ' + CAST(@L AS NVARCHAR),FLOOR(20000*RAND()))
SET @L +=1;
END

CHECKPOINT;
DBCC DROPCLEANBUFFERS

CREATE INDEX #TASK5IND ON #TASK5(Nomer)

INSERT TOP(10000) #TASK5(Nomer ,Stroka) SELECT Nomer, Stroka FROM #TASK5

ALTER INDEX #TASK5IND ON #TASK5 REORGANIZE

ALTER INDEX #TASK5IND ON #TASK5 REBUILD WITH (ONLINE = OFF)

SELECT NAME [ИНДЕКС], AVG_FRAGMENTATION_IN_PERCENT [ФРАГМЕНТАЦИЯ (%)] 
FROM SYS.DM_DB_INDEX_PHYSICAL_STATS(DB_ID(N'TEMPDB'),
OBJECT_ID(N'#TASK5'), NULL, NULL, NULL) SS
JOIN SYS.INDEXES II ON SS.OBJECT_ID = II.OBJECT_ID
AND SS.INDEX_ID = II.INDEX_ID WHERE NAME IS NOT NULL; 

DROP TABLE #TASK5;
/*6*/
--Разработать пример, демон-стрирующий применение параметра FILLFACTOR при создании некла-стеризованного индекса.
CREATE TABLE #TASK6
(
    Stroka NVARCHAR(20),
    Iterator INT IDENTITY(1, 1),
    Nomer INT 
);

DECLARE @O INT = 0;
WHILE @O <= 100000
BEGIN
    INSERT INTO #TASK6(Stroka, Nomer)
    VALUES ('СТРОКА' + CAST(@O AS NVARCHAR), FLOOR(20000 * RAND()));
    SET @O += 1;
END;

CREATE INDEX #TASK6IND ON #TASK6(Nomer) WITH (FILLFACTOR = 55);

INSERT TOP(50) PERCENT #TASK6(Nomer, Stroka)
SELECT Nomer, Stroka FROM #TASK6

SELECT NAME [Индекс], AVG_FRAGMENTATION_IN_PERCENT [Фрагментация (%)]
        FROM SYS.DM_DB_INDEX_PHYSICAL_STATS(DB_ID(N'TEMPDB'),
        OBJECT_ID(N'#TASK6'), NULL, NULL, NULL) SS
        JOIN SYS.INDEXES II ON SS.OBJECT_ID = II.OBJECT_ID AND SS.INDEX_ID = II.INDEX_ID WHERE NAME IS NOT NULL;

DROP INDEX #TASK6IND ON TASK6 
DROP TABLE #TASK6;

