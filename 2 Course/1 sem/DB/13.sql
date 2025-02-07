USE UNIVER;

/*1 Разработать хранимую процедуру без параметров с именем PSUBJECT. 
Процедура формирует результирующий набор на основе таблицы SUBJECT
Процедура должна возвращать количество строк, выведенных в результирующий набор.*/
CREATE PROCEDURE PSUBJECT
AS
BEGIN
DECLARE @K INT=(SELECT COUNT(*) FROM SUBJECT);
SELECT SUBJECT [Код], SUBJECT_NAME [Дисциплина], PULPIT [Кафедра] FROM SUBJECT;
RETURN @K;
END;

DECLARE @I INT=0;
EXEC @I=PSUBJECT;
PRINT 'Количество строк, выведенных в результирующий набор: '+CAST(@I AS VARCHAR(3));

/*2 Изменить процедуру PSUBJECT,таким образом, чтобы она принимала два параметра с именами @p и @c.
Параметр @p является входным, имеет тип varchar(20) и значение по умол-чанию NULL. Параметр @с является выходным, имеет тип INT.
Процедура PSUBJECT должна формировать результирующий набор, но при этом содержать строки, соответствующие коду кафедры, заданному параметром @p. 
Процедура должна формировать значение выходного параметра  равное количеству строк в результирующем наборе, 
а также возвращать значение к точке вызова, равное общему количеству дисциплин (количеству строк в таблице SUBJECT). 
*/
ALTER PROCEDURE PSUBJECT @P VARCHAR(20) = NULL, @C INT OUTPUT
 AS
   BEGIN
 SELECT * FROM SUBJECT WHERE SUBJECT.SUBJECT = @P;
 SET @C = @@ROWCOUNT;
 DECLARE @K INT = (SELECT COUNT(*) FROM SUBJECT);
 PRINT 'Параметры: @P='+@P+', @C='+CAST(@C AS VARCHAR(3));
 RETURN @K;
   END

DECLARE @N INT, @A INT, @X NVARCHAR(20);
EXEC @N = PSUBJECT 'ООП', @A OUTPUT;
PRINT 'Кол-во строк результ набора: ' + CAST(@A AS NVARCHAR(4))
PRINT 'Всего строк в SUBJECT: ' + CAST(@N AS NVARCHAR(4))

/*3 Создать временную локальную таблицу с именем #SUBJECT. 
Наименование и тип столбцов таблицы должны соответствовать столбцам результирующего набора процедуры PSUBJECT 
Изменить процедуру PSUBJECT чтобы она не содержала выходного параметра.
Применив конструкцию INSERT… EXECUTE с модифицированной процедурой PSUBJECT, добавить строки в таблицу #SUBJECT. 
*/
ALTER PROCEDURE PSUBJECT @P VARCHAR(20)
AS BEGIN
	SELECT * FROM SUBJECT WHERE SUBJECT = @P;
END;

CREATE TABLE #SUBJECT
(
	[SUBJECT] VARCHAR(20),
	[SUBJECT_NAME] VARCHAR(100),
	[PULPIT] VARCHAR(20)
);
INSERT #SUBJECT EXEC PSUBJECT @P = 'ООП';
INSERT #SUBJECT EXEC PSUBJECT @P = 'ОАИП';
SELECT * FROM #SUBJECT;

--DROP PROCEDURE PSUBJECT;

/*4 Разработать процедуру с именем PAUDITORI-UM_INSERT. Процедура принимает четыре входных параметра: @a, @n, @c и @t. 
Параметр @a имеет тип CHAR(20), параметр @n имеет тип VARCHAR(50), параметр @c имеет тип INT и значение по умолчанию 0, параметр @t имеет тип CHAR(10).
Процедура добавляет строку в таблицу AUDITO-RIUM. Значения столбцов  добавляемой строки задаются параметрами
Процедура PAUDITORIUM_INSERT должна применять механизм TRY/CATCH для обработки ошибок. 
Процедура должна возвращать к точке вызова значение -1 в том случае, если произошла ошибка и 1, если выполнение успешно. 
*/
CREATE PROCEDURE PAUDITORIUM_INSERT @A CHAR(20), @N VARCHAR(50), @C INT = 0, @T CHAR(10)
AS 
 BEGIN 
   BEGIN TRY
	INSERT INTO AUDITORIUM(AUDITORIUM, AUDITORIUM_TYPE, AUDITORIUM_CAPACITY, AUDITORIUM_NAME)
		VALUES(@A, @N, @C, @T);
	RETURN 1;
  END TRY
  BEGIN CATCH
	PRINT 'Номер ошибки: ' + CAST(ERROR_NUMBER() AS VARCHAR(6));
	PRINT 'Сообщение: ' + ERROR_MESSAGE();
	PRINT 'Уровень: ' + CAST(ERROR_SEVERITY() AS VARCHAR(6));
	PRINT 'Метка: ' + CAST(ERROR_STATE() AS VARCHAR(8));
	PRINT 'Номер строки: '  + CAST(ERROR_LINE() AS VARCHAR(8));
	IF ERROR_PROCEDURE() IS NOT NULL   
	PRINT 'Имя процедуры: ' + ERROR_PROCEDURE();
	RETURN -1;
  END CATCH;
END;


DECLARE @RC INT;  
EXEC @RC = PAUDITORIUM_INSERT @A = '100', @N = 'ЛК', @C = 30, @T = '100'; 
PRINT 'STATUS: ' + CAST(@RC AS VARCHAR(3));

SELECT * FROM AUDITORIUM WHERE AUDITORIUM.AUDITORIUM = '100'

DELETE AUDITORIUM WHERE AUDITORIUM='100';

--DROP PROCEDURE PAUDITORIUM_INSERT;

/*5 Разработать процедуру с именем SUBJECT_REPORT, формирующую в стандартный выходной поток отчет со списком дисциплин на конкретной кафедре. 
В отчет должны быть выведены краткие названия (поле SUBJECT) из таблицы SUBJECT в одну строку через запятую (использовать встроенную функцию RTRIM).
Процедура имеет входной параметр с именем @p типа CHAR(10), который предназначен для указания кода кафедры.
В том случае, если по заданному значению @p не-возможно определить код кафедры, процедура должна генерировать ошибку с сообщением ошибка в параметрах. 
Процедура SUBJECT_REPORT должна возвращать к точке вызова количество дисциплин, отображенных в отчете. 
*/
CREATE PROCEDURE SUBJECT_REPORT @P CHAR(10)
  AS DECLARE @RC INT = 0;
	BEGIN TRY
		IF NOT EXISTS (SELECT SUBJECT FROM SUBJECT WHERE PULPIT = @P)
			RAISERROR('Ошибка в параметрах', 11, 1);
		DECLARE @SUBS_LIST CHAR(300) = '', @SUB CHAR(10);
		DECLARE SUBJECTS CURSOR FOR
			SELECT SUBJECT FROM SUBJECT WHERE PULPIT = @P;
		OPEN SUBJECTS;
			FETCH SUBJECTS INTO @SUB;
			WHILE (@@FETCH_STATUS = 0)
				BEGIN
					SET @SUBS_LIST = RTRIM(@SUB) + ', ' + @SUBS_LIST;
					SET @RC += 1;		
					FETCH SUBJECTS INTO @SUB;
				END;
			PRINT 'Дисциплины на кафедре ' + RTRIM(@P) + ':';
			PRINT RTRIM(@SUBS_LIST);
		CLOSE SUBJECTS;
		DEALLOCATE SUBJECTS;
		RETURN @RC;
	END TRY
	BEGIN CATCH
		PRINT 'Номер ошибки: ' + CONVERT(VARCHAR, ERROR_NUMBER());
		PRINT 'Сообщение: ' + ERROR_MESSAGE();
		PRINT 'Уровень: ' + CONVERT(VARCHAR, ERROR_SEVERITY());
		PRINT 'Метка: ' + CONVERT(VARCHAR, ERROR_STATE());
		PRINT 'Номер строки: ' + CONVERT(VARCHAR, ERROR_LINE());
		IF ERROR_PROCEDURE() IS NOT NULL
			PRINT 'Имя процедуры: ' + ERROR_PROCEDURE();
		RETURN @RC;
	END CATCH;

DECLARE @U INT;
EXEC @U = SUBJECT_REPORT 'ИСИТ';
PRINT 'Количество дисциплин: ' + CONVERT(VARCHAR, @U);

--DROP PROCEDURE SUBJECT_REPORT

/*6 Разработать процедуру с именем PAUDITORI-UM_INSERTX. Процедура принимает пять входных параметров: @a, @n, @c, @t и @tn. 
Параметры  аналогичны параметрам процедуры PAUDITORIUM_INSERT. 
Процедура добавляет две строки. Первая строка до-бавляется в таблицу AUDITORIUM_TYPE. Значения столбцов AUDITORIUM_TYPE и AUDITORIUM_ TYPENAME задаются соответственно параметрами @t и @tn.
Вторая строка добавляется путем вызова процедуры PAUDITORIUM_INSERT.
Добавление строки в таблицу AUDITORIUM_ TYPE и вызов процедуры PAUDITORIUM_INSERT должны выполняться в рамках одной транзакции с уровнем изолированности SERIALIZABLE. 
В процедуре должна быть предусмотрена обработка ошибок с помощью механизма TRY/CATCH. 
Процедура PAUDITORIUM_INSERTX должна возвращать к точке вызова значение -1  если произошла ошибка и 1, если выполнения процедуры завершилось успешно. 
*/
CREATE PROCEDURE PAUDITORIUM_INSERTX
		@A CHAR(20),
		@N VARCHAR(50),
		@C INT = 0,
		@T CHAR(10),
		@TN VARCHAR(50)
AS BEGIN
DECLARE @RC INT = 1;
BEGIN TRY
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
	BEGIN TRAN
	INSERT INTO AUDITORIUM_TYPE(AUDITORIUM_TYPE, AUDITORIUM_TYPENAME)
				VALUES(@N, @TN);
	EXEC @RC = PAUDITORIUM_INSERT @A, @N, @C, @T;
	COMMIT TRAN;
	RETURN @RC;
END TRY
BEGIN CATCH
	PRINT 'Номер ошибки: ' + CAST(ERROR_NUMBER() AS VARCHAR(6));
	PRINT 'Сообщение: ' + ERROR_MESSAGE();
	PRINT 'Уровень: ' + CAST(ERROR_SEVERITY() AS VARCHAR(6));
	PRINT 'Метка: ' + CAST(ERROR_STATE() AS VARCHAR(8));
	PRINT 'Номер строки: ' + CAST(ERROR_LINE() AS VARCHAR(8));
	IF ERROR_PROCEDURE() IS NOT  NULL
	PRINT 'Имя процедуры: ' + ERROR_PROCEDURE();
	IF @@TRANCOUNT > 0 ROLLBACK TRAN ;
	RETURN -1;
END CATCH;
END;

DECLARE @K3 INT;
EXEC @K3 = PAUDITORIUM_INSERTX '102-3', @N = 'КГ', @C = 85, @T = '102-3', @TN = 'Процедура';
PRINT 'Код : ' + CAST(@K3 AS VARCHAR(3));

SELECT * FROM AUDITORIUM;
SELECT * FROM AUDITORIUM_TYPE;

DELETE AUDITORIUM WHERE AUDITORIUM='102-3';
DELETE AUDITORIUM_TYPE WHERE AUDITORIUM_TYPE='КГ';

--DROP PROCEDURE PAUDITORIUM_INSERTX;