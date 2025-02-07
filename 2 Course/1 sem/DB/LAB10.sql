/*1*/
--���������� ��� �������, ������� ������� � �� UNIVER. 
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
    INSERT #TASK1(Nomer, Stroka) VALUES (FLOOR(20000*RAND()), REPLICATE('���������', 2));
    IF (@I % 100 = 0) PRINT @I;
    SET @I = @I + 1;
END;
--����������� SELECT-������. ��-������ ���� ������� � ���������� ��� ���������
SELECT * FROM #TASK1 WHERE Nomer BETWEEN 1000 AND 1500 ORDER BY Nomer;

-- ��������� ����� ����������
SET SHOWPLAN_TEXT ON;
GO
SELECT * FROM #TASK1 WHERE Nomer BETWEEN 1000 AND 1500 ORDER BY Nomer;
GO
SET SHOWPLAN_TEXT OFF;
--������� ���������������� ������, ����������� ��������� SELECT-�������.
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
    VALUES ('���������' + CAST(@X AS NVARCHAR), FLOOR(20000 * RAND()))
    SET @X += 1;
END
--����������� SELECT-������. ��-������ ���� ������� � ���������� ��� ���������. 
SELECT * FROM #TASK2 WHERE Stroka = '���������2' AND Nomer >= 1000

CHECKPOINT;
DBCC DROPCLEANBUFFERS

--������� ������������������ ��-���������� ��������� ������. 
CREATE INDEX #TASK2_NONCL ON #TASK2(Stroka, Nomer)
--������� ��������� ������ ��-��������.
SELECT * FROM #TASK2 WHERE Stroka = '���������2' AND Nomer >= 1000

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
VALUES ('���������' + CAST(@H AS NVARCHAR),FLOOR(20000*RAND()))
SET @H +=1;
END
--����������� SELECT-������. ��-������ ���� ������� � ���������� ��� ���������. 
SELECT Stroka FROM #TASK3 WHERE Iterator <= 10000 
--������� ������������������ ��-���� ��������, ����������� ���-������ SELECT-�������. 
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
VALUES ('���������' + CAST(@M AS NVARCHAR),FLOOR(20000*RAND()))
SET @M +=1;
END
--����������� SELECT-������, ��-������ ���� ������� � ���������� ��� ���������. 
SELECT Iterator FROM #TASK4 
WHERE Iterator > 666 AND Iterator < 2000
--������� ������������������ ����������� ������, ����������� ��������� SELECT-�������
CREATE INDEX #NONCLASSFILTR ON #TASK4(Iterator)
WHERE (Iterator > 1500 AND Iterator < 2000)

CHECKPOINT;--������������ ��� ������������� ����������� ��������� �� ��������� ���� �� ����.
DBCC DROPCLEANBUFFERS--������������ ��� ������� ��������� ���� SQL Server.

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
VALUES ('���������' + CAST(@L AS NVARCHAR),FLOOR(20000*RAND()))
SET @L +=1;
END

CHECKPOINT;
DBCC DROPCLEANBUFFERS

CREATE INDEX #TASK5IND ON #TASK5(Nomer)

INSERT TOP(10000) #TASK5(Nomer ,Stroka) SELECT Nomer, Stroka FROM #TASK5

ALTER INDEX #TASK5IND ON #TASK5 REORGANIZE

ALTER INDEX #TASK5IND ON #TASK5 REBUILD WITH (ONLINE = OFF)

SELECT NAME [������], AVG_FRAGMENTATION_IN_PERCENT [������������ (%)] 
FROM SYS.DM_DB_INDEX_PHYSICAL_STATS(DB_ID(N'TEMPDB'),
OBJECT_ID(N'#TASK5'), NULL, NULL, NULL) SS
JOIN SYS.INDEXES II ON SS.OBJECT_ID = II.OBJECT_ID
AND SS.INDEX_ID = II.INDEX_ID WHERE NAME IS NOT NULL; 

DROP TABLE #TASK5;
/*6*/
--����������� ������, �����-���������� ���������� ��������� FILLFACTOR ��� �������� �����-�������������� �������.
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
    VALUES ('������' + CAST(@O AS NVARCHAR), FLOOR(20000 * RAND()));
    SET @O += 1;
END;

CREATE INDEX #TASK6IND ON #TASK6(Nomer) WITH (FILLFACTOR = 55);

INSERT TOP(50) PERCENT #TASK6(Nomer, Stroka)
SELECT Nomer, Stroka FROM #TASK6

SELECT NAME [������], AVG_FRAGMENTATION_IN_PERCENT [������������ (%)]
        FROM SYS.DM_DB_INDEX_PHYSICAL_STATS(DB_ID(N'TEMPDB'),
        OBJECT_ID(N'#TASK6'), NULL, NULL, NULL) SS
        JOIN SYS.INDEXES II ON SS.OBJECT_ID = II.OBJECT_ID AND SS.INDEX_ID = II.INDEX_ID WHERE NAME IS NOT NULL;

DROP INDEX #TASK6IND ON TASK6 
DROP TABLE #TASK6;

