/*1*/
-- DECLARE
DECLARE
  @A CHAR(1) = '�',
  @B NVARCHAR(3) = N'���',
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
--����������� ������, � ������� ����-�������� ����� ����������� ���������
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
SELECT @CAPACITY [����� �����������],
@TOTAL [���������� ���������],
@AVGCAPACITY [������� �����������],
@TOTALLESS [������ ��������],
@PROCENT [%]
END
ELSE PRINT '����� ����������� ��������� (' + CAST(@CAPACITY AS NVARCHAR(10)) + ') ������ 200.';
/*3*/
--����������� T-SQL-������, ��-����� ������� �� ������ ���������� ����������: 
PRINT '����� ������������ �����: ' + CAST(@@ROWCOUNT AS NVARCHAR);
PRINT '������ SQL Server: ' + CAST(@@VERSION AS VARCHAR);
PRINT '��������� ������������� ��������: ' + CAST(@@SPID AS NVARCHAR);
PRINT '��� ��������� ������: ' + CAST(@@ERROR AS VARCHAR);
PRINT '��� �������: ' + CAST(@@SERVERNAME AS VARCHAR);
PRINT '������� ����������� ����������: ' + CAST(@@TRANCOUNT AS NVARCHAR);
PRINT '�������� ���������� ���������� ����� ��������������� ������: ' + CAST(@@FETCH_STATUS AS NVARCHAR);
PRINT '������� ����������� ������� �����-����: ' + CAST(@@NESTLEVEL AS NVARCHAR);
/*4*/
--���������� �������� ���������� z
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
--�������������� ������� ��� �������� � ����������� 
DECLARE @LASTNAME NVARCHAR(20) = '��������',
@FIRSTNAME NVARCHAR(20) = '���������',
@SURNAME NVARCHAR(20) = '���������',
@LONGNAME NVARCHAR(50),
@SHORTNAME NVARCHAR(30);

SET @LONGNAME = @LASTNAME + ' ' + @FIRSTNAME + ' ' + @SURNAME;
SET @FIRSTNAME = SUBSTRING(@FIRSTNAME, 1,1)+'.';
SET @SURNAME = SUBSTRING(@SURNAME, 1,1)+'.';
SET @SHORTNAME = @LASTNAME + ' ' + @FIRSTNAME + ' ' + @SURNAME;

SELECT @LONGNAME [������] ,@SHORTNAME [�����������];
--����� ���������, � ������� ���� �������� � ��������� ������, � ����-������� �� ��������;
USE UNIVER;
SELECT STUDENT.NAME, STUDENT.BDAY, DATEDIFF(YEAR, STUDENT.BDAY, SYSDATETIME()) AS �������
FROM STUDENT
WHERE MONTH(STUDENT.BDAY) = MONTH(SYSDATETIME()) + 1;
--����� ��� ������, � ������� �������� ��������� ������ ������� ������� �� ��
DECLARE @GROUPNUMBER INT = 4;
SELECT STUDENT.NAME, DATENAME(dw, PROGRESS.PDATE) [���� ������]
FROM STUDENT 
JOIN PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
JOIN  GROUPS ON STUDENT.IDGROUP = GROUPS.IDGROUP
WHERE GROUPS.IDGROUP = @GROUPNUMBER AND  PROGRESS.SUBJECT = '����';
/*5 ������������������ ����������� IF� ELSE */
DECLARE @MAX_CAPACITY INT = (SELECT MAX(AUDITORIUM_CAPACITY) FROM AUDITORIUM);
IF @MAX_CAPACITY > 10
BEGIN
  PRINT '��� ������.';
END
ELSE
  PRINT '������ �� ���.';
/*6 ����������� ��������, � ������� � ������� CASE ������������� ������ */
USE UNIVER;
SELECT
  (CASE
    WHEN NOTE BETWEEN 0 AND 3 THEN '�� �����'
    WHEN NOTE BETWEEN 4 AND 5 THEN '������'
    WHEN NOTE BETWEEN 6 AND 7 THEN '������'
    WHEN NOTE BETWEEN 8 AND 10 THEN '�������'
  END) AS '������', COUNT(*) AS '� �������� �����'
FROM PROGRESS
GROUP BY
  (CASE
    WHEN NOTE BETWEEN 0 AND 3 THEN '�� �����'
    WHEN NOTE BETWEEN 4 AND 5 THEN '������'
    WHEN NOTE BETWEEN 6 AND 7 THEN '������'
    WHEN NOTE BETWEEN 8 AND 10 THEN '�������'
  END)
ORDER BY '� �������� �����' DESC;
/*7 ������� ��������� ��������� ������� �� ���� �������� � 10 �����, ��������� �� � ������� ����������. ������������ �������� WHILE*/
-- �������� ��������� ��������� �������
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
  VALUES (@Counter, '���-�� ' + CAST(@Counter AS NVARCHAR(50)), RAND() * 100);
  SET @Counter = @Counter + 1;
END;
SELECT * FROM #TempTable;
DROP TABLE #TempTable;
/*8 ����������� ������, ��������������� ������������� ��������� RETURN*/
DECLARE @Number INT = -5;
IF @Number > 0
BEGIN
    PRINT '����� �������������.';
    RETURN;
END
ELSE IF @Number < 0
BEGIN
    PRINT '����� �������������.';
    RETURN;
END
ELSE
BEGIN
    PRINT '����� ����� ����.';
    RETURN; 
END;
PRINT '���� ��� ���������� ����� ��������� RETURN.';
/*9 . ����������� �������� � ��������, � ������� ������������ ��� ��������� ������ ����� TRY � CATCH*/
USE UNIVER;
BEGIN TRY
UPDATE PROGRESS SET NOTE = '������ ������ INT!' WHERE NOTE = 9
END TRY
BEGIN CATCH
 PRINT '��� ��������� ������: ' + CAST(ERROR_NUMBER() AS NVARCHAR(10));
    PRINT '��������� �� ������: ' + ERROR_MESSAGE();
    PRINT '������ ���� ��������� ������: ' + CAST(ERROR_LINE() AS NVARCHAR(10));
    PRINT '���������, ��������� ������: ' + COALESCE(ERROR_PROCEDURE(), '�� ���������');
    PRINT '������� ����������� ������: ' + CAST(ERROR_SEVERITY() AS NVARCHAR(10));
    PRINT '��������� ������: ' + CAST(ERROR_STATE() AS NVARCHAR(10));
END CATCH