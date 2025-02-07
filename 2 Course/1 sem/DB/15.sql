USE UNIVER;
--DROP TABLE TR_AUDIT

/*1 С помощью сценария создать таблицу TR_AUDIT.
Таблица предназначена для добавления в нее строк триггерами. 
В столбец STMT триггер должен поместить событие, на которое он среагировал, а в столбец TRNAME - собственное имя. 
Разработать AFTER-триггер с именем TR_TEACHER_INS для таблицы TEACHER, реагирующий на событие INSERT. 
Триггер должен записывать строки вводимых данных в таблицу TR_AUDIT. В столбец СС помещаются значения столбцов вводимой строки. */
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
    PRINT 'Вставка';

    SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
    FROM INSERTED;

    SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;

    INSERT INTO TR_AUDIT (STMT, TRNAME, CC)
    VALUES ('INS', 'TR_TEACHER_INS', @IN);
END;
GO
INSERT INTO TEACHER (TEACHER, TEACHER_NAME, GENDER, PULPIT)
VALUES ('НАВ','Немкович Анастасия Вадимовна','Ж','ИСИТ')

SELECT * FROM TR_AUDIT
--DROP TRIGGER TR_AUDIT

/*2 Создать AFTER-триггер с именем TR_TEACHER_DEL для таблицы TEA-CHER, реагирующий на событие DELETE. 
Триггер должен записывать строку данных в таблицу TR_AUDIT для каждой удаляемой строки. 
В столбец СС помещаются значения столбца TEACHER удаляемой строки. */
IF OBJECT_ID('TR_TEACHER_DEL', 'TR') IS NOT NULL
    DROP TRIGGER TR_TEACHER_DEL;
GO
CREATE TRIGGER TR_TEACHER_DEL
ON TEACHER AFTER DELETE
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(300);
    PRINT 'Удаление';

    SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
    FROM DELETED;

  SET @IN = @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;

    INSERT INTO TR_AUDIT (STMT, TRNAME, CC)
    VALUES ('DEL', 'TR_TEACHER_DEL', @IN);
END;
GO
DELETE FROM TEACHER 
WHERE TEACHER = 'НАВ'
SELECT * FROM TR_AUDIT
--DROP TRIGGER TR_TEACHER_DEL

/*3 Создать AFTER-триггер с именем TR_TEACHER_UPD для таблицы TEA-CHER, реагирующий на событие UPDATE. 
Триггер должен записывать строку данных в таблицу TR_AUDIT для каждой изменяемой строки. 
В столбец СС помещаются значения столбцов изменяемой строки до и после изменения.*/
IF OBJECT_ID('TR_TEACHER_UPD', 'TR') IS NOT NULL
    DROP TRIGGER TR_TEACHER_UPD;
GO
CREATE TRIGGER TR_TEACHER_UPD
ON TEACHER AFTER UPDATE
AS
BEGIN
    DECLARE @Before_A1 CHAR(10), @Before_A2 VARCHAR(100), @Before_A3 CHAR(1), @Before_A4 CHAR(20);
    DECLARE @After_A1 CHAR(10), @After_A2 VARCHAR(100), @After_A3 CHAR(1), @After_A4 CHAR(20), @IN VARCHAR(600);
    PRINT 'Обновление';
    SELECT @Before_A1 = TEACHER, @Before_A2 = TEACHER_NAME, @Before_A3 = GENDER, @Before_A4 = PULPIT
    FROM DELETED;
    SELECT @After_A1 = TEACHER, @After_A2 = TEACHER_NAME, @After_A3 = GENDER, @After_A4 = PULPIT
    FROM INSERTED;
  SET @IN = 'До: ' + @Before_A1 + ' ' + @Before_A2 + ' ' + @Before_A3 + ' ' + @Before_A4 +
             '| После: ' + @After_A1 + ' ' + @After_A2 + ' ' + @After_A3 + ' ' + @After_A4;
    INSERT INTO TR_AUDIT (STMT, TRNAME, CC)
    VALUES ('UPD', 'TR_TEACHER_UPD', @IN);
END;
GO
INSERT INTO TEACHER (TEACHER, TEACHER_NAME, GENDER, PULPIT)
      VALUES ('НАВ','Немкович Анастасия Вадимовна','Ж','ИСИТ')
UPDATE TEACHER SET GENDER = 'М' WHERE TEACHER='НАВ'
SELECT * FROM TR_AUDIT
--DROP TRIGGER TR_TEACHER_UPD

/*4 Создать AFTER-триггер с именем TR_TEACHER для таблицы TEACHER, реа-гирующий на события INSERT, DELETE, UPDATE. 
Триггер должен записывать строку данных в таблицу TR_AUDIT для каждой изменяемой строки. 
В коде триггера определить событие, активизировавшее триггер и поместить в стол-бец СС соответствующую событию информа-цию. 
Разработать сценарий, демонстрирующий работоспособность триггера.  */
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
        SET @IN = 'До: ' + @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;

        SELECT @A1 = TEACHER, @A2 = TEACHER_NAME, @A3 = GENDER, @A4 = PULPIT
        FROM DELETED;
        SET @IN = @IN + '| После: ' + @A1 + ' ' + @A2 + ' ' + @A3 + ' ' + @A4;
        INSERT INTO TR_AUDIT(STMT, TRNAME, CC)
        VALUES('UPD', 'TR_TEACHER_UPD', @IN);
    END;

    RETURN;
END;

DELETE TEACHER WHERE TEACHER='НАВ'
INSERT INTO  TEACHER VALUES('НАВ', 'Немкович Анастасия', 'М', 'ИСиТ');
UPDATE TEACHER SET GENDER = 'Ж' WHERE TEACHER='НАВ'
SELECT * FROM TR_AUDIT


/*5 Разработать сценарий, который демонстрирует на примере базы данных UNIVER, что проверка ограничения целостности выполняется до срабатывания AFTER-триггера.*/
INSERT INTO TEACHER(TEACHER,TEACHER_NAME,GENDER,PULPIT)
VALUES ('АБВ','Ааааа Бббббб Ввввввв','Ж','ИСИТ')
UPDATE TEACHER SET GENDER = 'М' WHERE TEACHER='АБВ'
 SELECT * FROM TR_AUDIT
 SELECT *FROM TEACHER
UPDATE TEACHER set PULPIT = 'ОХ' where TEACHER = 'АБВ'

DELETE FROM TEACHER 
WHERE TEACHER = 'АБВ'

/*6 Создать для таблицы TEACHER три AFTER-триггера с именами: TR_TEACHER_ DEL1, TR_TEACHER_DEL2 и TR_TEA-CHER_ DEL3. 
Триггеры должны реагировать на событие DELETE и формировать соответ-ствующие строки в таблицу TR_AUDIT.  
Получить список триггеров таблицы TEACHER. 
Упорядочить выполнение триггеров для таблицы TEACHER, реагирующих на событие DELETE следующим образом: первым должен выполняться триггер с именем TR_TEA-CHER_DEL3, последним – триггер TR_TEACHER_DEL2. 
Использовать системные представления SYS.TRIGGERS и SYS.TRIGGERS_ EVENTS, а также системную процедуру SP_SETTRIGGERORDERS.  */

CREATE TRIGGER TR_TEACHER_DEL1
ON TEACHER AFTER DELETE
AS
BEGIN
    DECLARE @A1 CHAR(10), @A2 VARCHAR(100), @A3 CHAR(1), @A4 CHAR(20), @IN VARCHAR(300);
    PRINT 'DEL1: Удаление';
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
    PRINT 'DEL2: Удаление';
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
    PRINT 'DEL3: Удаление';
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


/*7 Разработать сценарий, демонстрирующий на примере базы данных UNIVER утверждение: 
AFTER-триггер является частью транзакции, в рамках которого выполняется оператор, активизировавший триггер.*/
CREATE TRIGGER PTRAN
	ON PULPIT AFTER INSERT, DELETE, UPDATE
	AS DECLARE @C INT = (SELECT COUNT (*) FROM PULPIT);
	 IF (@C >20)
	 BEGIN
       RAISERROR('Записей больше 20', 10, 1);
	 ROLLBACK;
	 END;
	 RETURN;

INSERT INTO PULPIT(PULPIT) VALUES ('ЛАЛАЛА')

/*8 Для таблицы FACULTY создать INSTEAD OF-триггер, запрещающий удаление строк в таблице. 
Разработать сценарий, который демонстри-рует на примере базы данных UNIVER, что проверка ограничения целостности выполнена, если есть INSTEAD OF-триггер.
С помощью оператора DROP удалить все DML-триггеры, созданные в этой лабораторной работе. */
CREATE TRIGGER F_INSTEAD_OF
	ON FACULTY INSTEAD OF DELETE
	AS
	    BEGIN
RAISERROR(N'Запрет удаления', 10, 1);
RETURN;	
END;
	
 DELETE FACULTY WHERE FACULTY = 'ПИМ1';
 SELECT * FROM FACULTY

 DROP TRIGGER F_INSTEAD_OF,PTRAN,TEACH_AFTER_DEL1,TEACH_AFTER_DEL2,TEACH_AFTER_DEL3,TR_TEACHER 
/*9 Создать DDL-триггер, реагирующий на все DDL-события в БД UNIVER. 
Триггер должен запрещать создавать новые таблицы и удалять существующие. 
Свое выполнение триггер должен сопровождать сообщением, которое содержит: тип события, имя и тип объекта, текст, в случае запрещения выполнения оператора. 
Разработать сценарий, демонстрирующий работу триггера. */
CREATE TRIGGER TR_TEACHER_DDL ON DATABASE FOR DDL_DATABASE_LEVEL_EVENTS  AS   
DECLARE @EVENT_TYPE VARCHAR(50) = EVENTDATA().value('(/EVENT_INSTANCE/EventType)[1]', 'varchar(50)')
DECLARE @OBJ_NAME VARCHAR(50) = EVENTDATA().value('(/EVENT_INSTANCE/ObjectName)[1]', 'varchar(50)')
DECLARE @OBJ_TYPE VARCHAR(50) = EVENTDATA().value('(/EVENT_INSTANCE/ObjectType)[1]', 'varchar(50)')
IF (@EVENT_TYPE = 'DROP_TABLE') OR (@EVENT_TYPE = 'CREATE_TABLE')
     BEGIN
       PRINT 'ТИП СОБЫТИЯ: '+@EVENT_TYPE;
       PRINT 'ИМЯ ОБЪЕКТА: '+@OBJ_NAME;
       PRINT 'ТИП ОБЪЕКТА: '+@OBJ_TYPE;
       RAISERROR( N'удаление запрещено', 16, 1);  
     ROLLBACK  
     END
RETURN;

DROP TABLE TR_AUDIT

DROP TRIGGER TR_TEACHER_DDL ON DATABASE;