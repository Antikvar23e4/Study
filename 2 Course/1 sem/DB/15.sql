USE UNIVER;
--DROP TABLE TR_AUDIT

/*1 � ������� �������� ������� ������� TR_AUDIT.
������� ������������� ��� ���������� � ��� ����� ����������. 
� ������� STMT ������� ������ ��������� �������, �� ������� �� �����������, � � ������� TRNAME - ����������� ���. 
����������� AFTER-������� � ������ TR_TEACHER_INS ��� ������� TEACHER, ����������� �� ������� INSERT. 
������� ������ ���������� ������ �������� ������ � ������� TR_AUDIT. � ������� �� ���������� �������� �������� �������� ������. */
CREATE TABLE TR_AUDIT
(
ID INT IDENTITY,
STMT VARCHAR(20)
CHECK (STMT IN ('INS', 'DEL', 'UPD')),
TRNAME VARCHAR(50),
CC VARCHAR(300)
)
IF OBJECT_ID('TR_TEACHER_INS', 'TR') IS NOT NULL
    DROP TRIGGER TR_TEACHER_INS;
GO
CREATE TRIGGER TR_TEACHER_INS
ON TEACHER AFTER INSERT
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(300);
    PRINT '�������';

    SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
    FROM INSERTED;

    SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;

    INSERT INTO TR_AUDIT (STMT, TRNAME, CC)
    VALUES ('INS', 'TR_TEACHER_INS', @IN);
END;
GO
INSERT INTO TEACHER (TEACHER, TEACHER_NAME, GENDER, PULPIT)
VALUES ('���','�������� ��������� ���������','�','����')

SELECT * FROM TR_AUDIT
--DROP TRIGGER TR_AUDIT

/*2 ������� AFTER-������� � ������ TR_TEACHER_DEL ��� ������� TEA-CHER, ����������� �� ������� DELETE. 
������� ������ ���������� ������ ������ � ������� TR_AUDIT ��� ������ ��������� ������. 
� ������� �� ���������� �������� ������� TEACHER ��������� ������. */
IF OBJECT_ID('TR_TEACHER_DEL', 'TR') IS NOT NULL
    DROP TRIGGER TR_TEACHER_DEL;
GO
CREATE TRIGGER TR_TEACHER_DEL
ON TEACHER AFTER DELETE
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(300);
    PRINT '��������';

    SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
    FROM DELETED;

  SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;

    INSERT INTO TR_AUDIT (STMT, TRNAME, CC)
    VALUES ('DEL', 'TR_TEACHER_DEL', @IN);
END;
GO
DELETE FROM TEACHER 
WHERE TEACHER = '���'
SELECT * FROM TR_AUDIT
--DROP TRIGGER TR_TEACHER_DEL

/*3 ������� AFTER-������� � ������ TR_TEACHER_UPD ��� ������� TEA-CHER, ����������� �� ������� UPDATE. 
������� ������ ���������� ������ ������ � ������� TR_AUDIT ��� ������ ���������� ������. 
� ������� �� ���������� �������� �������� ���������� ������ �� � ����� ���������.*/
IF OBJECT_ID('TR_TEACHER_UPD', 'TR') IS NOT NULL
    DROP TRIGGER TR_TEACHER_UPD;
GO
CREATE TRIGGER TR_TEACHER_UPD
ON TEACHER AFTER UPDATE
AS
BEGIN
    DECLARE @Before_A1 CHAR(10), @Before_A2 VARCHAR(100), @Before_A3 CHAR(1), @Before_A4 CHAR(20);
    DECLARE @After_A1 CHAR(10), @After_A2 VARCHAR(100), @After_A3 CHAR(1), @After_A4 CHAR(20), @IN VARCHAR(600);
    PRINT '����������';
    SELECT @Before_A1 = TEACHER, @Before_A2 = TEACHER_NAME, @Before_A3 = GENDER, @Before_A4 = PULPIT
    FROM DELETED;
    SELECT @After_A1 = TEACHER, @After_A2 = TEACHER_NAME, @After_A3 = GENDER, @After_A4 = PULPIT
    FROM INSERTED;
  SET @IN = '��: ' + @Before_A1 + ' ' + @Before_A2 + ' ' + @Before_A3 + ' ' + @Before_A4 +
             '| �����: ' + @After_A1 + ' ' + @After_A2 + ' ' + @After_A3 + ' ' + @After_A4;
    INSERT INTO TR_AUDIT (STMT, TRNAME, CC)
    VALUES ('UPD', 'TR_TEACHER_UPD', @IN);
END;
GO
INSERT INTO TEACHER (TEACHER, TEACHER_NAME, GENDER, PULPIT)
      VALUES ('���','�������� ��������� ���������','�','����')
UPDATE TEACHER SET GENDER = '�' WHERE TEACHER='���'
SELECT * FROM TR_AUDIT
--DROP TRIGGER TR_TEACHER_UPD

/*4 ������� AFTER-������� � ������ TR_TEACHER ��� ������� TEACHER, ���-�������� �� ������� INSERT, DELETE, UPDATE. 
������� ������ ���������� ������ ������ � ������� TR_AUDIT ��� ������ ���������� ������. 
� ���� �������� ���������� �������, ���������������� ������� � ��������� � ����-��� �� ��������������� ������� �������-���. 
����������� ��������, ��������������� ����������������� ��������.  */
IF OBJECT_ID('TR_TEACHER', 'TR') IS NOT NULL
    DROP TRIGGER TR_TEACHER;
GO
CREATE TRIGGER TR_TEACHER
ON TEACHER AFTER INSERT, DELETE, UPDATE
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(600);
    DECLARE @INS INT = (SELECT COUNT(*) FROM INSERTED),
            @DEL INT = (SELECT COUNT(*) FROM DELETED);
    IF @INS > 0 AND @DEL = 0
    BEGIN

        PRINT 'INSERT';
        SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
        FROM INSERTED;
        SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;
        INSERT INTO TR_AUDIT(STMT, TRNAME, CC)
        VALUES('INS', 'TR_TEACHER_INS', @IN);
    END;
    ELSE IF @INS = 0 AND @DEL > 0
    BEGIN

        PRINT 'DELETE';
        SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
        FROM DELETED;
        SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;
        INSERT INTO TR_AUDIT(STMT, TRNAME, CC)
        VALUES('DEL', 'TR_TEACHER_DEL', @IN);
    END;
    ELSE
    BEGIN

        PRINT 'UPDATE';
        SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
        FROM INSERTED;
        SET @IN = '��: ' + @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;

        SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
        FROM DELETED;
        SET @IN = @IN + '| �����: ' + @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;
        INSERT INTO TR_AUDIT(STMT, TRNAME, CC)
        VALUES('UPD', 'TR_TEACHER_UPD', @IN);
    END;

    RETURN;
END;

DELETE TEACHER WHERE TEACHER='���'
INSERT INTO  TEACHER VALUES('���', '�������� ���������', '�', '����');
UPDATE TEACHER SET GENDER = '�' WHERE TEACHER='���'
SELECT * FROM TR_AUDIT


/*5 ����������� ��������, ������� ������������� �� ������� ���� ������ UNIVER, ��� �������� ����������� ����������� ����������� �� ������������ AFTER-��������.*/
INSERT INTO TEACHER(TEACHER,TEACHER_NAME,GENDER,PULPIT)
VALUES ('���','����� ������ �������','�','����')
UPDATE TEACHER SET GENDER = '�' WHERE TEACHER='���'
 SELECT * FROM TR_AUDIT
 SELECT *FROM TEACHER
UPDATE TEACHER set PULPIT = '��' where TEACHER = '���'

DELETE FROM TEACHER 
WHERE TEACHER = '���'

/*6 ������� ��� ������� TEACHER ��� AFTER-�������� � �������: TR_TEACHER_ DEL1, TR_TEACHER_DEL2 � TR_TEA-CHER_ DEL3. 
�������� ������ ����������� �� ������� DELETE � ����������� �������-�������� ������ � ������� TR_AUDIT.  
�������� ������ ��������� ������� TEACHER. 
����������� ���������� ��������� ��� ������� TEACHER, ����������� �� ������� DELETE ��������� �������: ������ ������ ����������� ������� � ������ TR_TEA-CHER_DEL3, ��������� � ������� TR_TEACHER_DEL2. 
������������ ��������� ������������� SYS.TRIGGERS � SYS.TRIGGERS_ EVENTS, � ����� ��������� ��������� SP_SETTRIGGERORDERS.  */

CREATE TRIGGER TR_TEACHER_DEL1
ON TEACHER AFTER DELETE
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(300);
    PRINT 'DEL1: ��������';
    SELECT TOP 1 @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
    FROM DELETED;
    SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;
    INSERT INTO TR_AUDIT(STMT, TRNAME, CC)
    VALUES ('DEL', 'TR_TEACHER_DEL1', @IN);
END;
GO

CREATE TRIGGER TR_TEACHER_DEL2
ON TEACHER AFTER DELETE
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(300);
    PRINT 'DEL2: ��������';
    SELECT TOP 1 @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
    FROM DELETED;
    SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;
    INSERT INTO TR_AUDIT(STMT, TRNAME, CC)
    VALUES ('DEL', 'TR_TEACHER_DEL2', @IN);
END;
GO

CREATE TRIGGER TR_TEACHER_DEL3
ON TEACHER AFTER DELETE
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(300);
    PRINT 'DEL3: ��������';
    SELECT TOP 1 @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
    FROM DELETED;
    SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;
    INSERT INTO TR_AUDIT(STMT, TRNAME, CC)
    VALUES ('DEL', 'TR_TEACHER_DEL3', @IN);
END;
GO

SELECT NAME
FROM SYS.TRIGGERS 
WHERE PARENT_ID = OBJECT_ID('TEACHER');
GO
EXEC  SP_SETTRIGGERORDER @TRIGGERNAME = 'TEACH_AFTER_DEL3', @ORDER='FIRST', @STMTTYPE = 'DELETE';
EXEC  SP_SETTRIGGERORDER @TRIGGERNAME = 'TEACH_AFTER_DEL2', @ORDER='LAST', @STMTTYPE = 'DELETE';


/*7 ����������� ��������, ��������������� �� ������� ���� ������ UNIVER �����������: 
AFTER-������� �������� ������ ����������, � ������ �������� ����������� ��������, ���������������� �������.*/
CREATE TRIGGER PTRAN
	ON PULPIT AFTER INSERT, DELETE, UPDATE
	AS DECLARE @C INT = (SELECT COUNT (*) FROM PULPIT);
	 IF (@C >20)
	 BEGIN
       RAISERROR('������� ������ 20', 10, 1);
	 ROLLBACK;
	 END;
	 RETURN;

INSERT INTO PULPIT(PULPIT) VALUES ('������')

/*8 ��� ������� FACULTY ������� INSTEAD OF-�������, ����������� �������� ����� � �������. 
����������� ��������, ������� ���������-���� �� ������� ���� ������ UNIVER, ��� �������� ����������� ����������� ���������, ���� ���� INSTEAD OF-�������.
� ������� ��������� DROP ������� ��� DML-��������, ��������� � ���� ������������ ������. */
CREATE TRIGGER F_INSTEAD_OF
	ON FACULTY INSTEAD OF DELETE
	AS
	    BEGIN
RAISERROR(N'������ ��������', 10, 1);
RETURN;	
END;
	
 DELETE FACULTY WHERE FACULTY = '���1';
 SELECT * FROM FACULTY

 DROP TRIGGER F_INSTEAD_OF,PTRAN,TEACH_AFTER_DEL1,TEACH_AFTER_DEL2,TEACH_AFTER_DEL3,TR_TEACHER 
/*9 ������� DDL-�������, ����������� �� ��� DDL-������� � �� UNIVER. 
������� ������ ��������� ��������� ����� ������� � ������� ������������. 
���� ���������� ������� ������ ������������ ����������, ������� ��������: ��� �������, ��� � ��� �������, �����, � ������ ���������� ���������� ���������. 
����������� ��������, ��������������� ������ ��������. */
CREATE TRIGGER TR_TEACHER_DDL ON DATABASE FOR DDL_DATABASE_LEVEL_EVENTS  AS   
DECLARE @EVENT_TYPE VARCHAR(50) = EVENTDATA().value('(/EVENT_INSTANCE/EventType)[1]', 'varchar(50)')
DECLARE @OBJ_NAME VARCHAR(50) = EVENTDATA().value('(/EVENT_INSTANCE/ObjectName)[1]', 'varchar(50)')
DECLARE @OBJ_TYPE VARCHAR(50) = EVENTDATA().value('(/EVENT_INSTANCE/ObjectType)[1]', 'varchar(50)')
IF (@EVENT_TYPE = 'DROP_TABLE') OR (@EVENT_TYPE = 'CREATE_TABLE')
     BEGIN
       PRINT '��� �������: '+@EVENT_TYPE;
       PRINT '��� �������: '+@OBJ_NAME;
       PRINT '��� �������: '+@OBJ_TYPE;
       RAISERROR( N'�������� ���������', 16, 1);  
     ROLLBACK  
     END
RETURN;

DROP TABLE TR_AUDIT

DROP TRIGGER TR_TEACHER_DDL ON DATABASE;