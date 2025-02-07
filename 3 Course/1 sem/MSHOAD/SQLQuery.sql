USE TourAgency;
GO

CREATE TABLE Route (
    RouteID INT PRIMARY KEY,
    Name NVARCHAR(255) NOT NULL,
    Description NVARCHAR(255),
    Country NVARCHAR(100)
);

CREATE TABLE Attractions (
    AttractionId INT PRIMARY KEY,
    Name NVARCHAR(255) NOT NULL,
    Description NVARCHAR(255),
    RouteId INT NOT NULL,
    FOREIGN KEY (RouteId) REFERENCES Route(RouteID) ON DELETE CASCADE
);

CREATE TABLE Tours (
    TourId INT PRIMARY KEY,
    Name NVARCHAR(255) NOT NULL,
    RouteId INT NOT NULL,
    Price DECIMAL(10, 2) NOT NULL,
    DepartureDate DATE NOT NULL,
    ReturnDate DATE NOT NULL,
    FOREIGN KEY (RouteId) REFERENCES Route(RouteID) ON DELETE CASCADE
);

CREATE TABLE Employees (
    EmployeeId INT PRIMARY KEY,
    Name NVARCHAR(255) NOT NULL,
    SecondName NVARCHAR(255),
    PhoneNumber NVARCHAR(20),
    Salary DECIMAL(10, 2),
    Job NVARCHAR(100)
);

CREATE TABLE Clients (
    ClientId INT PRIMARY KEY,
    Name NVARCHAR(255) NOT NULL,
    SecondName NVARCHAR(255) NOT NULL,
    PhoneNumber NVARCHAR(20)NOT NULL,
    Email NVARCHAR(255),
    Passport NVARCHAR(50) NOT NULL
);

CREATE TABLE Sales (
    SaleId INT PRIMARY KEY,
    TourId INT NOT NULL,
    EmployeeId INT NOT NULL,
    ClientId INT NOT NULL,
    SaleData DATE NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (TourId) REFERENCES Tours(TourId) ON DELETE CASCADE,
    FOREIGN KEY (EmployeeId) REFERENCES Employees(EmployeeId) ON DELETE CASCADE,
    FOREIGN KEY (ClientId) REFERENCES Clients(ClientId) ON DELETE CASCADE
);

-- Последовательности
CREATE SEQUENCE seq_Route AS INT START WITH 4 INCREMENT BY 1;
CREATE SEQUENCE seq_Attractions AS INT START WITH 4 INCREMENT BY 1;
CREATE SEQUENCE seq_Tours AS INT START WITH 4 INCREMENT BY 1;
CREATE SEQUENCE seq_Employees AS INT START WITH 4 INCREMENT BY 1;
CREATE SEQUENCE seq_Clients AS INT START WITH 4 INCREMENT BY 1;
CREATE SEQUENCE seq_Sales AS INT START WITH 4 INCREMENT BY 1;


-- Индексы
CREATE INDEX idx_Route_Country ON Route (Country);
CREATE INDEX idx_Sales_TourId ON Sales (TourId);
CREATE INDEX idx_Sales_EmployeeId ON Sales (EmployeeId);
CREATE INDEX idx_Sales_ClientId ON Sales (ClientId);

-- Процедуры
CREATE PROCEDURE AddRoute
    @Name NVARCHAR(255),
    @Description NVARCHAR(255) = NULL,
    @Country NVARCHAR(100)
AS
BEGIN
    INSERT INTO Route (RouteID, Name, Description, Country)
    VALUES (NEXT VALUE FOR seq_Route, @Name, @Description, @Country);
END;


CREATE PROCEDURE AddAttraction
    @Name NVARCHAR(255),
    @Description NVARCHAR(255) = NULL,
    @RouteId INT
AS
BEGIN
    INSERT INTO Attractions (AttractionId, Name, Description, RouteId)
    VALUES (NEXT VALUE FOR seq_Attractions, @Name, @Description, @RouteId);
END;


CREATE PROCEDURE AddTour
    @Name NVARCHAR(255),
    @RouteId INT,
    @Price DECIMAL(10, 2),
    @DepartureDate DATE,
    @ReturnDate DATE
AS
BEGIN
    INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
    VALUES (NEXT VALUE FOR seq_Tours, @Name, @RouteId, @Price, @DepartureDate, @ReturnDate);
END;


CREATE PROCEDURE AddClient
    @Name NVARCHAR(255),
    @SecondName NVARCHAR(255),
    @PhoneNumber NVARCHAR(20),
    @Email NVARCHAR(255) = NULL,
    @Passport NVARCHAR(50)
AS
BEGIN
    INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
    VALUES (NEXT VALUE FOR seq_Clients, @Name, @SecondName, @PhoneNumber, @Email, @Passport);
END;


CREATE PROCEDURE UpdateClient
    @ClientId INT,
    @Name NVARCHAR(255) = NULL,
    @SecondName NVARCHAR(255) = NULL,
    @PhoneNumber NVARCHAR(20) = NULL,
    @Email NVARCHAR(255) = NULL,
    @Passport NVARCHAR(50) = NULL
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Clients WHERE ClientId = @ClientId)
    BEGIN
        UPDATE Clients
        SET
            Name = ISNULL(@Name, Name),
            SecondName = ISNULL(@SecondName, SecondName),
            PhoneNumber = ISNULL(@PhoneNumber, PhoneNumber),
            Email = ISNULL(@Email, Email),
            Passport = ISNULL(@Passport, Passport)
        WHERE ClientId = @ClientId;
    END
END;


-- Представления
CREATE VIEW View_ToursRoutesAttractions
AS
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
GO

CREATE VIEW View_SalesInfo
AS
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
GO

--Функции
CREATE FUNCTION dbo.GetToursSoldByEmployee
(
    @EmployeeId INT
)
RETURNS TABLE
AS
RETURN 
(
    SELECT 
        COUNT(*) AS TotalSalesCount,
        SUM(t.Price) AS TotalSalesAmount
    FROM 
        Sales s
    JOIN 
        Tours t ON s.TourId = t.TourId
    WHERE 
        s.EmployeeId = @EmployeeId
);

--Триггеры
CREATE TRIGGER trg_AfterUpdateClient
ON Clients
AFTER UPDATE
AS
BEGIN
    DECLARE @ClientId INT;
    SELECT @ClientId = ClientId FROM INSERTED;
    PRINT 'Клиент обновлён: ID = ' + CAST(@ClientId AS NVARCHAR(10));
END;



INSERT INTO Route (RouteID, Name, Description, Country) VALUES
(1, 'Морское побережье', 'Отдых на пляже с солнцем и морем', 'Испания'),
(2, 'Горный поход', 'Походы по горам с захватывающими видами', 'Швейцария'),
(3, 'Культурный тур', 'Посещение исторических мест и музеев', 'Италия');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId) VALUES
(1, 'Пляж Коста Брава', 'Известный пляж с золотым песком', 1),
(2, 'Вершина Маттерхорн', 'Одна из самых известных гор Европы', 2),
(3, 'Колизей', 'Древнеримский амфитеатр', 3),
(4, 'Собор Святого Петра', 'Крупнейшая католическая церковь в мире', 3);
INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate) VALUES
(1, 'Летний отдых в Испании', 1, 1500.00, '2024-06-01', '2024-06-15'),
(2, 'Поход по Альпам', 2, 1200.00, '2024-07-01', '2024-07-10'),
(3, 'Экскурсия по Риму', 3, 800.00, '2024-08-01', '2024-08-07');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job) VALUES
(1, 'Александр', 'Иванов', '1234567890', 50000.00, 'Менеджер по продажам'),
(2, 'Мария', 'Петрова', '0987654321', 45000.00, 'Менеджер по трам'),
(3, 'Сергей', 'Сидоров', '1122334455', 60000.00, 'Менеджер по продажам');
INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport) VALUES
(1, 'Иван', 'Смирнов', '5555555555', 'ivan@example.com', '1234567890'),
(2, 'Елена', 'Кузнецова', '4444444444', 'elena@example.com', '0987654321'),
(3, 'Дмитрий', 'Федоров', '3333333333', 'dmitry@example.com', '1122334455');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData) VALUES
(1, 1, 1, 1, '2024-01-15'),
(2, 2, 2, 2, '2024-02-20'),
(3, 3, 3, 3, '2024-03-10');

SELECT * FROM Route;
SELECT * FROM Attractions;
SELECT * FROM Tours;
SELECT * FROM Employees;
SELECT * FROM Clients;
SELECT * FROM Sales;

SELECT * FROM View_ToursRoutesAttractions;
SELECT * FROM View_SalesInfo;


    EXEC AddRoute 
        @Name = 'Прекрасный маршрут',
        @Description = 'Этот маршрут проходит через живописные места.',
        @Country = 'Россия';
SELECT * FROM Route;

    EXEC AddAttraction 
        @Name = 'Слоновая гора',
        @Description = 'Гора, на которой можно увидеть слонов.',
        @RouteId = 1;
SELECT * FROM Attractions;

    EXEC AddTour 
        @Name = 'Летний тур',
        @RouteId = 1,
        @Price = 15000.00,
        @DepartureDate = '2024-06-01',
        @ReturnDate = '2024-06-15';
SELECT * FROM Tours;

    EXEC AddClient 
        @Name = 'Иван',
        @SecondName = 'Смирнов',
        @PhoneNumber = '1234567890',
        @Email = 'ivan@example.com',
        @Passport = '1234 567890';
SELECT * FROM Clients;

    EXEC UpdateClient 
        @ClientId = 1,
        @Name = 'Иван',
        @SecondName = 'Смирнов',
        @PhoneNumber = '9876543210';

DECLARE @EmployeeId INT = 1;
SELECT * FROM dbo.GetToursSoldByEmployee(@EmployeeId);


