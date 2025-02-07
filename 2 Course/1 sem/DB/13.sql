USE UNIVER;

/*1 ����������� �������� ��������� ��� ���������� � ������ PSUBJECT. 
��������� ��������� �������������� ����� �� ������ ������� SUBJECT
��������� ������ ���������� ���������� �����, ���������� � �������������� �����.*/
CREATE PROCEDURE PSUBJECT
AS
BEGIN
DECLARE @K INT=(SELECT COUNT(*) FROM SUBJECT);
SELECT SUBJECT [���], SUBJECT_NAME [����������], PULPIT [�������] FROM SUBJECT;
RETURN @K;
END;

DECLARE @I INT=0;
EXEC @I=PSUBJECT;
PRINT '���������� �����, ���������� � �������������� �����: '+CAST(@I AS VARCHAR(3));

/*2 �������� ��������� PSUBJECT,����� �������, ����� ��� ��������� ��� ��������� � ������� @p � @c.
�������� @p �������� �������, ����� ��� varchar(20) � �������� �� ����-����� NULL. �������� @� �������� ��������, ����� ��� INT.
��������� PSUBJECT ������ ����������� �������������� �����, �� ��� ���� ��������� ������, ��������������� ���� �������, ��������� ���������� @p. 
��������� ������ ����������� �������� ��������� ���������  ������ ���������� ����� � �������������� ������, 
� ����� ���������� �������� � ����� ������, ������ ������ ���������� ��������� (���������� ����� � ������� SUBJECT). 
*/
ALTER PROCEDURE PSUBJECT @P VARCHAR(20) = NULL, @C INT OUTPUT
 AS
   BEGIN
 SELECT * FROM SUBJECT WHERE SUBJECT.SUBJECT = @P;
 SET @C = @@ROWCOUNT;
 DECLARE @K INT = (SELECT COUNT(*) FROM SUBJECT);
 PRINT '���������: @P='+@P+', @C='+CAST(@C AS VARCHAR(3));
 RETURN @K;
   END

DECLARE @N INT, @A INT, @X NVARCHAR(20);
EXEC @N = PSUBJECT '���', @A OUTPUT;
PRINT '���-�� ����� ������� ������: ' + CAST(@A AS NVARCHAR(4))
PRINT '����� ����� � SUBJECT: ' + CAST(@N AS NVARCHAR(4))

/*3 ������� ��������� ��������� ������� � ������ #SUBJECT. 
������������ � ��� �������� ������� ������ ��������������� �������� ��������������� ������ ��������� PSUBJECT 
�������� ��������� PSUBJECT ����� ��� �� ��������� ��������� ���������.
�������� ����������� INSERT� EXECUTE � ���������������� ���������� PSUBJECT, �������� ������ � ������� #SUBJECT. 
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
INSERT #SUBJECT EXEC PSUBJECT @P = '���';
INSERT #SUBJECT EXEC PSUBJECT @P = '����';
SELECT * FROM #SUBJECT;

--DROP PROCEDURE PSUBJECT;

/*4 ����������� ��������� � ������ PAUDITORI-UM_INSERT. ��������� ��������� ������ ������� ���������: @a, @n, @c � @t. 
�������� @a ����� ��� CHAR(20), �������� @n ����� ��� VARCHAR(50), �������� @c ����� ��� INT � �������� �� ��������� 0, �������� @t ����� ��� CHAR(10).
��������� ��������� ������ � ������� AUDITO-RIUM. �������� ��������  ����������� ������ �������� �����������
��������� PAUDITORIUM_INSERT ������ ��������� �������� TRY/CATCH ��� ��������� ������. 
��������� ������ ���������� � ����� ������ �������� -1 � ��� ������, ���� ��������� ������ � 1, ���� ���������� �������. 
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
	PRINT '����� ������: ' + CAST(ERROR_NUMBER() AS VARCHAR(6));
	PRINT '���������: ' + ERROR_MESSAGE();
	PRINT '�������: ' + CAST(ERROR_SEVERITY() AS VARCHAR(6));
	PRINT '�����: ' + CAST(ERROR_STATE() AS VARCHAR(8));
	PRINT '����� ������: '  + CAST(ERROR_LINE() AS VARCHAR(8));
	IF ERROR_PROCEDURE() IS NOT NULL   
	PRINT '��� ���������: ' + ERROR_PROCEDURE();
	RETURN -1;
  END CATCH;
END;


DECLARE @RC INT;  
EXEC @RC = PAUDITORIUM_INSERT @A = '100', @N = '��', @C = 30, @T = '100'; 
PRINT 'STATUS: ' + CAST(@RC AS VARCHAR(3));

SELECT * FROM AUDITORIUM WHERE AUDITORIUM.AUDITORIUM = '100'

DELETE AUDITORIUM WHERE AUDITORIUM='100';

--DROP PROCEDURE PAUDITORIUM_INSERT;

/*5 ����������� ��������� � ������ SUBJECT_REPORT, ����������� � ����������� �������� ����� ����� �� ������� ��������� �� ���������� �������. 
� ����� ������ ���� �������� ������� �������� (���� SUBJECT) �� ������� SUBJECT � ���� ������ ����� ������� (������������ ���������� ������� RTRIM).
��������� ����� ������� �������� � ������ @p ���� CHAR(10), ������� ������������ ��� �������� ���� �������.
� ��� ������, ���� �� ��������� �������� @p ��-�������� ���������� ��� �������, ��������� ������ ������������ ������ � ���������� ������ � ����������. 
��������� SUBJECT_REPORT ������ ���������� � ����� ������ ���������� ���������, ������������ � ������. 
*/
CREATE PROCEDURE SUBJECT_REPORT @P CHAR(10)
  AS DECLARE @RC INT = 0;
	BEGIN TRY
		IF NOT EXISTS (SELECT SUBJECT FROM SUBJECT WHERE PULPIT = @P)
			RAISERROR('������ � ����������', 11, 1);
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
			PRINT '���������� �� ������� ' + RTRIM(@P) + ':';
			PRINT RTRIM(@SUBS_LIST);
		CLOSE SUBJECTS;
		DEALLOCATE SUBJECTS;
		RETURN @RC;
	END TRY
	BEGIN CATCH
		PRINT '����� ������: ' + CONVERT(VARCHAR, ERROR_NUMBER());
		PRINT '���������: ' + ERROR_MESSAGE();
		PRINT '�������: ' + CONVERT(VARCHAR, ERROR_SEVERITY());
		PRINT '�����: ' + CONVERT(VARCHAR, ERROR_STATE());
		PRINT '����� ������: ' + CONVERT(VARCHAR, ERROR_LINE());
		IF ERROR_PROCEDURE() IS NOT NULL
			PRINT '��� ���������: ' + ERROR_PROCEDURE();
		RETURN @RC;
	END CATCH;

DECLARE @U INT;
EXEC @U = SUBJECT_REPORT '����';
PRINT '���������� ���������: ' + CONVERT(VARCHAR, @U);

--DROP PROCEDURE SUBJECT_REPORT

/*6 ����������� ��������� � ������ PAUDITORI-UM_INSERTX. ��������� ��������� ���� ������� ����������: @a, @n, @c, @t � @tn. 
���������  ���������� ���������� ��������� PAUDITORIUM_INSERT. 
��������� ��������� ��� ������. ������ ������ ��-��������� � ������� AUDITORIUM_TYPE. �������� �������� AUDITORIUM_TYPE � AUDITORIUM_ TYPENAME �������� �������������� ����������� @t � @tn.
������ ������ ����������� ����� ������ ��������� PAUDITORIUM_INSERT.
���������� ������ � ������� AUDITORIUM_ TYPE � ����� ��������� PAUDITORIUM_INSERT ������ ����������� � ������ ����� ���������� � ������� ��������������� SERIALIZABLE. 
� ��������� ������ ���� ������������� ��������� ������ � ������� ��������� TRY/CATCH. 
��������� PAUDITORIUM_INSERTX ������ ���������� � ����� ������ �������� -1  ���� ��������� ������ � 1, ���� ���������� ��������� ����������� �������. 
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
	PRINT '����� ������: ' + CAST(ERROR_NUMBER() AS VARCHAR(6));
	PRINT '���������: ' + ERROR_MESSAGE();
	PRINT '�������: ' + CAST(ERROR_SEVERITY() AS VARCHAR(6));
	PRINT '�����: ' + CAST(ERROR_STATE() AS VARCHAR(8));
	PRINT '����� ������: ' + CAST(ERROR_LINE() AS VARCHAR(8));
	IF ERROR_PROCEDURE() IS NOT  NULL
	PRINT '��� ���������: ' + ERROR_PROCEDURE();
	IF @@TRANCOUNT > 0 ROLLBACK TRAN ;
	RETURN -1;
END CATCH;
END;

DECLARE @K3 INT;
EXEC @K3 = PAUDITORIUM_INSERTX '102-3', @N = '��', @C = 85, @T = '102-3', @TN = '���������';
PRINT '��� : ' + CAST(@K3 AS VARCHAR(3));

SELECT * FROM AUDITORIUM;
SELECT * FROM AUDITORIUM_TYPE;

DELETE AUDITORIUM WHERE AUDITORIUM='102-3';
DELETE AUDITORIUM_TYPE WHERE AUDITORIUM_TYPE='��';

--DROP PROCEDURE PAUDITORIUM_INSERTX;