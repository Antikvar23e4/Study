/*1*/
-- DECLARE
DECLARE
  @A CHAR(1) = 'А',
  @B NVARCHAR(3) = N'ФИТ',
  @C DATETIME = GETDATE(),
  @D TIME,
  @E INT,
  @F SMALLINT,
  @G TINYINT,
  @H NUMERIC(12,5);
-- SET
SET @D = GETDATE();
SET @E = 12345678;
SET @F = 123;
SET @G = 1;
-- SELECT
SELECT
  @A AS 'A',
  @B AS 'B',
  @C AS 'C',
  @D AS 'D';
--  PRINT
PRINT 'E = ' + CONVERT(NVARCHAR, @E)+ ' F = '+ CONVERT(NVARCHAR, @F) + ' G = '+ CONVERT(NVARCHAR, @G);
/*2*/
--Разработать скрипт, в котором опре-деляется общая вместимость аудиторий
USE UNIVER;

DECLARE 
@CAPACITY INT = (SELECT SUM(AUDITORIUM_CAPACITY) FROM AUDITORIUM),
@TOTAL INT,
@AVGCAPACITY INT,
@TOTALLESS INT,
@PROCENT INT;

IF @CAPACITY > 200
BEGIN
SET @TOTAL = (SELECT COUNT(*) FROM AUDITORIUM);
SET @AVGCAPACITY = (SELECT AVG(AUDITORIUM_CAPACITY) FROM AUDITORIUM);
SET @TOTALLESS= (SELECT COUNT(*) FROM AUDITORIUM
WHERE AUDITORIUM_CAPACITY < @AVGCAPACITY);
SET @PROCENT = @TOTALLESS * 100 / @TOTAL;
SELECT @CAPACITY [Общая вместимость],
@TOTAL [Количество аудиторий],
@AVGCAPACITY [Средняя вместимость],
@TOTALLESS [Меньше среднего],
@PROCENT [%]
END
ELSE PRINT 'Общая вместимость аудиторий (' + CAST(@CAPACITY AS NVARCHAR(10)) + ') меньше 200.';
/*3*/
--Разработать T-SQL-скрипт, ко-торый выводит на печать глобальные переменные: 
PRINT 'Число обработанных строк: ' + CAST(@@ROWCOUNT AS NVARCHAR);
PRINT 'Версия SQL Server: ' + CAST(@@VERSION AS VARCHAR);
PRINT 'Системный идентификатор процесса: ' + CAST(@@SPID AS NVARCHAR);
PRINT 'Код последней ошибки: ' + CAST(@@ERROR AS VARCHAR);
PRINT 'Имя сервера: ' + CAST(@@SERVERNAME AS VARCHAR);
PRINT 'Уровень вложенности транзакции: ' + CAST(@@TRANCOUNT AS NVARCHAR);
PRINT 'Проверка результата считывания строк результирующего набора: ' + CAST(@@FETCH_STATUS AS NVARCHAR);
PRINT 'Уровень вложенности текущей проце-дуры: ' + CAST(@@NESTLEVEL AS NVARCHAR);
/*4*/
--вычисление значений переменной z
DECLARE 
@Z FLOAT,
@T FLOAT = 47,
@X FLOAT = 6;

IF @T > @X
SET @Z = POWER(SIN(@T), 2);

ELSE IF @T < @X
SET @Z = 4*(@T + @X);

ELSE
SET @Z = 1 - EXP(@X-2);

SELECT @Z [z] ;
--преобразование полного ФИО студента в сокращенное 
DECLARE @LASTNAME NVARCHAR(20) = 'Немкович',
@FIRSTNAME NVARCHAR(20) = 'Анастасия',
@SURNAME NVARCHAR(20) = 'Вадимовна',
@LONGNAME NVARCHAR(50),
@SHORTNAME NVARCHAR(30);

SET @LONGNAME = @LASTNAME + ' ' + @FIRSTNAME + ' ' + @SURNAME;
SET @FIRSTNAME = SUBSTRING(@FIRSTNAME, 1,1)+'.';
SET @SURNAME = SUBSTRING(@SURNAME, 1,1)+'.';
SET @SHORTNAME = @LASTNAME + ' ' + @FIRSTNAME + ' ' + @SURNAME;

SELECT @LONGNAME [Полное] ,@SHORTNAME [Сокращенное];
--поиск студентов, у которых день рождения в следующем месяце, и опре-деление их возраста;
USE UNIVER;
SELECT STUDENT.NAME, STUDENT.BDAY, DATEDIFF(YEAR, STUDENT.BDAY, SYSDATETIME()) AS ВОЗРАСТ
FROM STUDENT
WHERE MONTH(STUDENT.BDAY) = MONTH(SYSDATETIME()) + 1;
--поиск дня недели, в который студенты некоторой группы сдавали экзамен по БД
DECLARE @GROUPNUMBER INT = 4;
SELECT STUDENT.NAME, DATENAME(dw, PROGRESS.PDATE) [День недели]
FROM STUDENT 
JOIN PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
JOIN  GROUPS ON STUDENT.IDGROUP = GROUPS.IDGROUP
WHERE GROUPS.IDGROUP = @GROUPNUMBER AND  PROGRESS.SUBJECT = 'СУБД';
/*5 Продемонстрировать конструкцию IF… ELSE */
DECLARE @MAX_CAPACITY INT = (SELECT MAX(AUDITORIUM_CAPACITY) FROM AUDITORIUM);
IF @MAX_CAPACITY > 10
BEGIN
  PRINT 'Все влезут.';
END
ELSE
  PRINT 'Влезут не все.';
/*6 Разработать сценарий, в котором с помощью CASE анализируются оценки */
USE UNIVER;
SELECT
  (CASE
    WHEN NOTE BETWEEN 0 AND 3 THEN 'Не сдано'
    WHEN NOTE BETWEEN 4 AND 5 THEN 'Сойдет'
    WHEN NOTE BETWEEN 6 AND 7 THEN 'Хорошо'
    WHEN NOTE BETWEEN 8 AND 10 THEN 'Отлично'
  END) AS 'Оценка', COUNT(*) AS 'У скольких людей'
FROM PROGRESS
GROUP BY
  (CASE
    WHEN NOTE BETWEEN 0 AND 3 THEN 'Не сдано'
    WHEN NOTE BETWEEN 4 AND 5 THEN 'Сойдет'
    WHEN NOTE BETWEEN 6 AND 7 THEN 'Хорошо'
    WHEN NOTE BETWEEN 8 AND 10 THEN 'Отлично'
  END)
ORDER BY 'У скольких людей' DESC;
/*7 Создать временную локальную таблицу из трех столбцов и 10 строк, заполнить ее и вывести содержимое. Использовать оператор WHILE*/
-- Создание временной локальной таблицы
CREATE TABLE #TempTable
(
  ID INT,
  Name NVARCHAR(50),
  Value INT
);
DECLARE @Counter INT = 1;

WHILE @Counter <= 10
BEGIN
  INSERT INTO #TempTable (ID, Name, Value)
  VALUES (@Counter, 'ЧТО-ТО ' + CAST(@Counter AS NVARCHAR(50)), RAND() * 100);
  SET @Counter = @Counter + 1;
END;
SELECT * FROM #TempTable;
DROP TABLE #TempTable;
/*8 Разработать скрипт, демонстрирующий использование оператора RETURN*/
DECLARE @Number INT = -5;
IF @Number > 0
BEGIN
    PRINT 'Число положительное.';
    RETURN;
END
ELSE IF @Number < 0
BEGIN
    PRINT 'Число отрицательное.';
    RETURN;
END
ELSE
BEGIN
    PRINT 'Число равно нулю.';
    RETURN; 
END;
PRINT 'Этот код выполнится после оператора RETURN.';
/*9 . Разработать сценарий с ошибками, в котором используются для обработки ошибок блоки TRY и CATCH*/
USE UNIVER;
BEGIN TRY
UPDATE PROGRESS SET NOTE = 'СТРОКА ВМЕСТО INT!' WHERE NOTE = 9
END TRY
BEGIN CATCH
 PRINT 'Код последней ошибки: ' + CAST(ERROR_NUMBER() AS NVARCHAR(10));
    PRINT 'Сообщение об ошибке: ' + ERROR_MESSAGE();
    PRINT 'Строка кода последней ошибки: ' + CAST(ERROR_LINE() AS NVARCHAR(10));
    PRINT 'Процедура, вызвавшая ошибку: ' + COALESCE(ERROR_PROCEDURE(), 'Не применимо');
    PRINT 'Уровень серьезности ошибки: ' + CAST(ERROR_SEVERITY() AS NVARCHAR(10));
    PRINT 'Состояние ошибки: ' + CAST(ERROR_STATE() AS NVARCHAR(10));
END CATCH