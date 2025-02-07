CREATE USER Lab8 IDENTIFIED BY 12345;

GRANT CREATE TYPE TO Lab8;
GRANT CREATE SESSION TO Lab8;
GRANT CREATE PUBLIC SYNONYM TO Lab8;

GRANT CREATE TABLE TO Lab8;
GRANT ALTER ANY TABLE TO Lab8;
GRANT DROP ANY TABLE TO Lab8;

GRANT
    CREATE SESSION,
    CREATE TABLE,
    CREATE VIEW,
    CREATE PROCEDURE,
    CREATE SEQUENCE,
    CREATE TRIGGER,
    CREATE ANY INDEX,
    
    ALTER ANY TABLE,
    ALTER ANY PROCEDURE,
    ALTER ANY SEQUENCE,
    ALTER ANY TRIGGER,
    ALTER ANY INDEX,
    
    DROP ANY TABLE,
    DROP ANY VIEW,
    DROP ANY PROCEDURE,
    DROP ANY SEQUENCE,
    DROP ANY TRIGGER,
    DROP ANY INDEX
TO Lab8;

COMMIT;

ALTER USER Lab8 QUOTA UNLIMITED ON USERS;

--Клиенты и туры
--Создать объектные типы данных по своему варианту, реализовав:
--a.	Дополнительный конструктор;
--b.	Метод сравнения типа MAP или ORDER;
--c.	Метод экземпляра функцию;
--d.	Метод экземпляра процедуру.
CREATE OR REPLACE TYPE Client_obj AS OBJECT (
    ClientId NUMBER,
    Name VARCHAR2(255),
    SecondName VARCHAR2(255),
    PhoneNumber VARCHAR2(20),
    Email VARCHAR2(255),
    Passport VARCHAR2(50),

    CONSTRUCTOR FUNCTION Client_obj(
        ClientId NUMBER,
        Name VARCHAR2,
        SecondName VARCHAR2,
        PhoneNumber VARCHAR2,
        Email VARCHAR2,
        Passport VARCHAR2
    ) RETURN SELF AS RESULT,

    MAP MEMBER FUNCTION to_number RETURN NUMBER,
    MEMBER FUNCTION get_full_name RETURN VARCHAR2,
    MEMBER PROCEDURE update_contact_info(newPhoneNumber VARCHAR2, newEmail VARCHAR2)
);

CREATE OR REPLACE TYPE BODY Client_obj AS
    CONSTRUCTOR FUNCTION Client_obj(
        ClientId NUMBER,
        Name VARCHAR2,
        SecondName VARCHAR2,
        PhoneNumber VARCHAR2,
        Email VARCHAR2,
        Passport VARCHAR2
    ) RETURN SELF AS RESULT IS
    BEGIN
        SELF.ClientId := ClientId;
        SELF.Name := Name;
        SELF.SecondName := SecondName;
        SELF.PhoneNumber := PhoneNumber;
        SELF.Email := Email;
        SELF.Passport := Passport;
        RETURN;
    END;

    MAP MEMBER FUNCTION to_number RETURN NUMBER IS
    BEGIN
        RETURN SELF.ClientId;
    END;

    MEMBER FUNCTION get_full_name RETURN VARCHAR2 IS
    BEGIN
        RETURN SELF.Name || ' ' || SELF.SecondName;
    END;

    MEMBER PROCEDURE update_contact_info(newPhoneNumber VARCHAR2, newEmail VARCHAR2) IS
    BEGIN
        SELF.PhoneNumber := newPhoneNumber;
        SELF.Email := newEmail;
    END;
END;


CREATE OR REPLACE TYPE Tour_obj AS OBJECT (
    TourId NUMBER,
    Name VARCHAR2(255),
    RouteId NUMBER,
    Price NUMBER(10, 2),
    DepartureDate DATE,
    ReturnDate DATE,

    CONSTRUCTOR FUNCTION Tour_obj(
        TourId NUMBER,
        Name VARCHAR2,
        RouteId NUMBER,
        Price NUMBER,
        DepartureDate DATE,
        ReturnDate DATE
    ) RETURN SELF AS RESULT,

    MAP MEMBER FUNCTION to_number RETURN NUMBER,
    MEMBER FUNCTION calculate_duration RETURN NUMBER,
    MEMBER PROCEDURE update_price(newPrice NUMBER)
);

CREATE OR REPLACE TYPE BODY Tour_obj AS
    CONSTRUCTOR FUNCTION Tour_obj(
        TourId NUMBER,
        Name VARCHAR2,
        RouteId NUMBER,
        Price NUMBER,
        DepartureDate DATE,
        ReturnDate DATE
    ) RETURN SELF AS RESULT IS
    BEGIN
        SELF.TourId := TourId;
        SELF.Name := Name;
        SELF.RouteId := RouteId;
        SELF.Price := Price;
        SELF.DepartureDate := DepartureDate;
        SELF.ReturnDate := ReturnDate;
        RETURN;
    END;

    MAP MEMBER FUNCTION to_number RETURN NUMBER IS
    BEGIN
        RETURN SELF.Price;
    END;

    MEMBER FUNCTION calculate_duration RETURN NUMBER IS
    BEGIN
        RETURN ReturnDate - DepartureDate;
    END;

    MEMBER PROCEDURE update_price(newPrice NUMBER) IS
    BEGIN
        SELF.Price := newPrice;
    END;
END;

-- Скопировать данные из реляционных таблиц в объектные.

CREATE TABLE Clients_Object_Table OF Client_obj;
INSERT INTO Clients_Object_Table
SELECT
    Client_obj(
        ClientId,
        Name,
        SecondName,
        PhoneNumber,
        Email,
        Passport
    )
FROM Clients;
COMMIT;

SELECT * FROM Clients_Object_Table;

CREATE TABLE Tours_Object_Table OF Tour_obj;
INSERT INTO Tours_Object_Table
SELECT
    Tour_obj(
        TourId,
        Name,
        RouteId,
        Price,
        DepartureDate,
        ReturnDate
    )
FROM Tours;
COMMIT;
SELECT * FROM Tours_Object_Table;

-- Продемонстрировать применение объектных представлений.

CREATE OR REPLACE VIEW Clients_View AS
SELECT
    Client_obj(
        ClientId,
        Name,
        SecondName,
        PhoneNumber,
        Email,
        Passport
    ) AS client_data
FROM Clients;

SELECT c.client_data.ClientId, 
       c.client_data.Name, 
       c.client_data.SecondName,
       c.client_data.Email
FROM Clients_View c;

SELECT c.client_data.get_full_name() AS full_name
FROM Clients_View c;

CREATE OR REPLACE VIEW Tours_View AS
SELECT
    Tour_obj(
        TourId,
        Name,
        RouteId,
        Price,
        DepartureDate,
        ReturnDate
    ) AS tour_data
FROM Tours;

SELECT t.tour_data.TourId AS Tour_Id,
       t.tour_data.Name AS Tour_Name,
       t.tour_data.Price AS Tour_Price
FROM Tours_View t;

SELECT t.tour_data.TourId AS Tour_Id,
       t.tour_data.Name AS Tour_Name,
       t.tour_data.calculate_duration() AS Duration
FROM Tours_View t;

--Продемонстрировать применение индексов для индексирования по атрибуту и по методу в объектной таблице.
CREATE TABLE CLT (
    CLIENT_DATA Client_obj
);

INSERT INTO CLT (CLIENT_DATA)
VALUES (Client_obj(1, 'John', 'Smith', '1234567890', 'john.smith@example.com', 'A1234567'));

COMMIT;

CREATE BITMAP INDEX IDX_CLT_ID ON CLT(CLIENT_DATA.ClientId);
SELECT * FROM CLT;
SELECT CL.CLIENT_DATA.ClientId FROM CLT CL;

SELECT INDEX_NAME, TABLE_NAME, INDEX_TYPE
FROM USER_INDEXES
WHERE INDEX_NAME = 'IDX_CLT_ID';

CREATE OR REPLACE TYPE Client_obj_new AS OBJECT (
    ClientId NUMBER,
    Name VARCHAR2(255),
    SecondName VARCHAR2(255),
    PhoneNumber VARCHAR2(20),
    Email VARCHAR2(255),
    Passport VARCHAR2(50),

    CONSTRUCTOR FUNCTION Client_obj_new(
        ClientId NUMBER,
        Name VARCHAR2,
        SecondName VARCHAR2,
        PhoneNumber VARCHAR2,
        Email VARCHAR2,
        Passport VARCHAR2
    ) RETURN SELF AS RESULT,

    -- Метод get_full_name с добавленным DETERMINISTIC
    MEMBER FUNCTION get_full_name RETURN VARCHAR2 DETERMINISTIC
);


CREATE OR REPLACE TYPE BODY Client_obj_new AS
    CONSTRUCTOR FUNCTION Client_obj_new(
        ClientId NUMBER,
        Name VARCHAR2,
        SecondName VARCHAR2,
        PhoneNumber VARCHAR2,
        Email VARCHAR2,
        Passport VARCHAR2
    ) RETURN SELF AS RESULT IS
    BEGIN
        SELF.ClientId := ClientId;
        SELF.Name := Name;
        SELF.SecondName := SecondName;
        SELF.PhoneNumber := PhoneNumber;
        SELF.Email := Email;
        SELF.Passport := Passport;
        RETURN;
    END;

    MEMBER FUNCTION get_full_name RETURN VARCHAR2 DETERMINISTIC IS
    BEGIN
        RETURN SELF.Name || ' ' || SELF.SecondName;
    END;
END;


CREATE TABLE CLT_NEW (
    CLIENT_DATA Client_obj_new
);

INSERT INTO CLT_NEW (CLIENT_DATA)
VALUES (Client_obj_new(1, 'John', 'Smith', '1234567890', 'john.smith@example.com', 'A1234567'));
COMMIT;

CREATE BITMAP INDEX IDX_CLT_NEW_getfullname ON CLT_NEW(CLIENT_DATA.get_full_name());
SELECT * FROM CLT_NEW;
SELECT CL.CLIENT_DATA.get_full_name() FROM CLT_NEW CL;

SELECT INDEX_NAME, TABLE_NAME, INDEX_TYPE
FROM USER_INDEXES
WHERE INDEX_NAME = 'IDX_CLT_NEW_GETFULLNAME';
