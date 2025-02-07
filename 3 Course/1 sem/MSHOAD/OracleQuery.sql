-- Создание таблиц
CREATE TABLE Route (
    RouteID NUMBER PRIMARY KEY,
    Name VARCHAR2(255) NOT NULL,
    Description VARCHAR2(255),
    Country VARCHAR2(100)
);

CREATE TABLE Attractions (
    AttractionId NUMBER PRIMARY KEY,
    Name VARCHAR2(255) NOT NULL,
    Description VARCHAR2(255),
    RouteId NUMBER NOT NULL,
    FOREIGN KEY (RouteId) REFERENCES Route(RouteID) ON DELETE CASCADE
);

CREATE TABLE Tours (
    TourId NUMBER PRIMARY KEY,
    Name VARCHAR2(255) NOT NULL,
    RouteId NUMBER NOT NULL,
    Price NUMBER(10, 2) NOT NULL,
    DepartureDate DATE NOT NULL,
    ReturnDate DATE NOT NULL,
    FOREIGN KEY (RouteId) REFERENCES Route(RouteID) ON DELETE CASCADE
);

CREATE TABLE Employees (
    EmployeeId NUMBER PRIMARY KEY,
    Name VARCHAR2(255) NOT NULL,
    SecondName VARCHAR2(255),
    PhoneNumber VARCHAR2(20),
    Salary NUMBER(10, 2),
    Job VARCHAR2(100)
);

CREATE TABLE Clients (
    ClientId NUMBER PRIMARY KEY,
    Name VARCHAR2(255) NOT NULL,
    SecondName VARCHAR2(255) NOT NULL,
    PhoneNumber VARCHAR2(20) NOT NULL,
    Email VARCHAR2(255),
    Passport VARCHAR2(50) NOT NULL
);

CREATE TABLE Sales (
    SaleId NUMBER PRIMARY KEY,
    TourId NUMBER NOT NULL,
    EmployeeId NUMBER NOT NULL,
    ClientId NUMBER NOT NULL,
    SaleData DATE DEFAULT SYSDATE NOT NULL,
    FOREIGN KEY (TourId) REFERENCES Tours(TourId) ON DELETE CASCADE,
    FOREIGN KEY (EmployeeId) REFERENCES Employees(EmployeeId) ON DELETE CASCADE,
    FOREIGN KEY (ClientId) REFERENCES Clients(ClientId) ON DELETE CASCADE
);

-- Последовательности
CREATE SEQUENCE seq_Route START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Attractions START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Tours START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Employees START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Clients START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Sales START WITH 1 INCREMENT BY 1;

-- Индексы
CREATE INDEX idx_Route_Country ON Route (Country);
CREATE INDEX idx_Sales_TourId ON Sales (TourId);
CREATE INDEX idx_Sales_EmployeeId ON Sales (EmployeeId);
CREATE INDEX idx_Sales_ClientId ON Sales (ClientId);

-- Процедуры
CREATE OR REPLACE PROCEDURE AddRoute (
    p_Name IN VARCHAR2,
    p_Description IN VARCHAR2 DEFAULT NULL,
    p_Country IN VARCHAR2
) AS
BEGIN
    INSERT INTO Route (RouteID, Name, Description, Country)
    VALUES (seq_Route.NEXTVAL, p_Name, p_Description, p_Country);
END;

CREATE OR REPLACE PROCEDURE AddAttraction (
    p_Name IN VARCHAR2,
    p_Description IN VARCHAR2 DEFAULT NULL,
    p_RouteId IN NUMBER
) AS
BEGIN
    INSERT INTO Attractions (AttractionId, Name, Description, RouteId)
    VALUES (seq_Attractions.NEXTVAL, p_Name, p_Description, p_RouteId);
END;

CREATE OR REPLACE PROCEDURE AddTour (
    p_Name IN VARCHAR2,
    p_RouteId IN NUMBER,
    p_Price IN NUMBER,
    p_DepartureDate IN DATE,
    p_ReturnDate IN DATE
) AS
BEGIN
    INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
    VALUES (seq_Tours.NEXTVAL, p_Name, p_RouteId, p_Price, p_DepartureDate, p_ReturnDate);
END;

CREATE OR REPLACE PROCEDURE AddClient (
    p_Name IN VARCHAR2,
    p_SecondName IN VARCHAR2,
    p_PhoneNumber IN VARCHAR2,
    p_Email IN VARCHAR2 DEFAULT NULL,
    p_Passport IN VARCHAR2
) AS
BEGIN
    INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
    VALUES (seq_Clients.NEXTVAL, p_Name, p_SecondName, p_PhoneNumber, p_Email, p_Passport);
END;

CREATE OR REPLACE PROCEDURE UpdateClient (
    p_ClientId IN NUMBER,
    p_Name IN VARCHAR2 DEFAULT NULL,
    p_SecondName IN VARCHAR2 DEFAULT NULL,
    p_PhoneNumber IN VARCHAR2 DEFAULT NULL,
    p_Email IN VARCHAR2 DEFAULT NULL,
    p_Passport IN VARCHAR2 DEFAULT NULL
) AS
BEGIN
    UPDATE Clients
    SET 
        Name = COALESCE(p_Name, Name),
        SecondName = COALESCE(p_SecondName, SecondName),
        PhoneNumber = COALESCE(p_PhoneNumber, PhoneNumber),
        Email = COALESCE(p_Email, Email),
        Passport = COALESCE(p_Passport, Passport)
    WHERE ClientId = p_ClientId;
END;

-- Представления
CREATE OR REPLACE VIEW View_ToursRoutesAttractions AS
SELECT 
    t.TourId,
    t.Name AS TourName,
    t.Price,
    t.DepartureDate,
    t.ReturnDate,
    r.RouteID,
    r.Name AS RouteName,
    r.Country,
    a.AttractionId,
    a.Name AS AttractionName,
    a.Description AS AttractionDescription
FROM 
    Tours t
JOIN 
    Route r ON t.RouteId = r.RouteID
JOIN 
    Attractions a ON r.RouteID = a.RouteId;

CREATE OR REPLACE VIEW View_SalesInfo AS
SELECT 
    s.SaleId,
    s.SaleData,
    t.TourId,
    t.Name AS TourName,
    t.Price,
    c.ClientId,
    c.Name AS ClientName,
    c.SecondName AS ClientSecondName,
    e.EmployeeId,
    e.Name AS EmployeeName,
    e.SecondName AS EmployeeSecondName
FROM 
    Sales s
JOIN 
    Tours t ON s.TourId = t.TourId
JOIN 
    Clients c ON s.ClientId = c.ClientId
JOIN 
    Employees e ON s.EmployeeId = e.EmployeeId;

-- Функция
CREATE OR REPLACE FUNCTION GetToursSoldByEmployee (
    p_EmployeeId IN NUMBER
) RETURN VARCHAR2 AS
    v_TotalSalesCount NUMBER;
    v_TotalSalesAmount NUMBER;
BEGIN
    -- Запрос на подсчет проданных туров
    SELECT COUNT(*)
    INTO v_TotalSalesCount
    FROM Sales s
    WHERE s.EmployeeId = p_EmployeeId;

    -- Запрос на сумму продаж
    SELECT NVL(SUM(t.Price), 0)
    INTO v_TotalSalesAmount
    FROM Sales s
    JOIN Tours t ON s.TourId = t.TourId
    WHERE s.EmployeeId = p_EmployeeId;

    -- Выводим результаты
    DBMS_OUTPUT.PUT_LINE('Количество проданных туров: ' || v_TotalSalesCount);
    DBMS_OUTPUT.PUT_LINE('Сумма продаж: ' || v_TotalSalesAmount);

    RETURN 'Успешно выполнено';
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Нет данных для указанного сотрудника.');
        RETURN 'Нет данных';
END;


-- Триггер
CREATE OR REPLACE TRIGGER trg_AfterUpdateClient
AFTER UPDATE ON Clients
FOR EACH ROW
BEGIN
    DBMS_OUTPUT.PUT_LINE('Клиент обновлён: ID = ' || :NEW.ClientId);
END;


-- Демонстрация
BEGIN
    AddRoute('Морское побережье', 'Отдых на пляже с солнцем и морем', 'Испания');
    AddRoute('Горный поход', 'Походы по горам с захватывающими видами', 'Швейцария');
    AddRoute('Культурный тур', 'Посещение исторических мест и музеев', 'Италия');
END;
SELECT * FROM ROUTE;

BEGIN
    AddAttraction('Пляж Коста Брава', 'Известный пляж с золотым песком', 1);
    AddAttraction('Вершина Маттерхорн', 'Одна из самых известных гор Европы', 2);
    AddAttraction('Колизей', 'Древнеримский амфитеатр', 3);
    AddAttraction('Собор Святого Петра', 'Крупнейшая католическая церковь в мире', 3);
END;
SELECT * FROM ATTRACTIONS;


BEGIN
    AddTour('Летний отдых в Испании', 1, 1500.00, TO_DATE('2024-06-01', 'YYYY-MM-DD'), TO_DATE('2024-06-15', 'YYYY-MM-DD'));
    AddTour('Поход по Альпам', 2, 1200.00, TO_DATE('2024-07-01', 'YYYY-MM-DD'), TO_DATE('2024-07-10', 'YYYY-MM-DD'));
    AddTour('Экскурсия по Риму', 3, 800.00, TO_DATE('2024-08-01', 'YYYY-MM-DD'), TO_DATE('2024-08-07', 'YYYY-MM-DD'));
END;
SELECT * FROM Tours;

BEGIN
    AddClient('Иван', 'Смирнов', '5555555555', 'ivan@example.com', '1234567890');
    AddClient('Елена', 'Кузнецова', '4444444444', 'elena@example.com', '0987654321');
    AddClient('Дмитрий', 'Федоров', '3333333333', 'dmitry@example.com', '1122334455');
END;
SELECT * FROM CLIENTS;

INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job) 
VALUES (1, 'Александр', 'Иванов', '1234567890', 50000.00, 'Менеджер по продажам');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job) 
VALUES (2, 'Мария', 'Петрова', '0987654321', 45000.00, 'Менеджер по туризму');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job) 
VALUES (3, 'Сергей', 'Сидоров', '1122334455', 60000.00, 'Менеджер по продажам');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job) 
VALUES (4, 'Елена', 'Кузнецова', '2233445566', 55000.00, 'Специалист по маркетингу');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job) 
VALUES (5, 'Дмитрий', 'Федоров', '3344556677', 47000.00, 'Менеджер по обслуживанию клиентов');

SELECT * FROM Employees;


BEGIN
    INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData) 
    VALUES (seq_Sales.NEXTVAL, 1, 1, 1, TO_DATE('2024-01-15', 'YYYY-MM-DD'));

    INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData) 
    VALUES (seq_Sales.NEXTVAL, 2, 2, 2, TO_DATE('2024-02-20', 'YYYY-MM-DD'));

    INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData) 
    VALUES (seq_Sales.NEXTVAL, 3, 3, 3, TO_DATE('2024-03-10', 'YYYY-MM-DD'));

END;

SELECT * FROM Sales;

SELECT * FROM View_ToursRoutesAttractions;

SELECT * FROM View_SalesInfo;

SET SERVEROUTPUT ON; 

DECLARE
    v_Result VARCHAR2(100);
BEGIN
    v_Result := GetToursSoldByEmployee(1); 
    DBMS_OUTPUT.PUT_LINE(v_Result); 
END;


