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


ALTER TABLE Attractions
ADD AttractionType NVARCHAR2(100);




CREATE SEQUENCE seq_Route START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Attractions START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Tours START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Employees START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Clients START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Sales START WITH 1 INCREMENT BY 1;

INSERT INTO Route (RouteID, Name, Description, Country)
VALUES (seq_Route.NEXTVAL, 'Тур по Камчатке', 'Экспедиция по Камчатке, вулканы и горячие источники', 'Россия');
INSERT INTO Route (RouteID, Name, Description, Country)
VALUES (seq_Route.NEXTVAL, 'Парижская прогулка', 'Тур по достопримечательностям Парижа', 'Франция');
INSERT INTO Route (RouteID, Name, Description, Country)
VALUES (seq_Route.NEXTVAL, 'Сафари в Кении', 'Тур по Кении с посещением национальных парков', 'Кения');
INSERT INTO Route (RouteID, Name, Description, Country)
VALUES (seq_Route.NEXTVAL, 'Экспедиция в Антарктиду', 'Путешествие на южный континент, наблюдение за пингвинами', 'Антарктида');

-- Для маршрута "Тур по Камчатке" (RouteID = 1)
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (1, 'Ключевской вулкан', 'Самый высокий вулкан в Евразии', 1, 'Природное чудо');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (2, 'Гейзерная долина', 'Знаменитая долина с множеством гейзеров', 1, 'Природное чудо');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (3, 'Лувр', 'Один из крупнейших музеев мира', 2, 'Культурный объект');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (4, 'Собор Парижской Богоматери', 'Знаменитый готический собор', 2, 'Исторический памятник');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (5, 'Национальный парк Масаи Мара', 'Известный заповедник с богатой фауной', 3, 'Природное чудо');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (6, 'Рифты Восточной Африки', 'Уникальные геологические образования', 3, 'Природное чудо');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (7, 'Колония пингвинов', 'Большие колонии императорских пингвинов', 4, 'Природное чудо');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (8, 'Ледяные шельфы Антарктиды', 'Гигантские ледяные массивы', 4, 'Природное чудо');

COMMIT



INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Камчатка: Огненная Земля', 1, 1500.00, TO_DATE('2024-06-10', 'YYYY-MM-DD'), TO_DATE('2024-06-20', 'YYYY-MM-DD'));
INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Камчатка: Весеннее путешествие', 1, 120000, TO_DATE('2024-02-01', 'YYYY-MM-DD'), TO_DATE('2024-02-10', 'YYYY-MM-DD'));
INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Камчатка: test', 1, 7000, TO_DATE('2024-02-01', 'YYYY-MM-DD'), TO_DATE('2024-02-10', 'YYYY-MM-DD'));

INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Париж и его секреты', 2, 2000.00, TO_DATE('2024-07-15', 'YYYY-MM-DD'), TO_DATE('2024-07-25', 'YYYY-MM-DD'));
INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Париж: VIP прогулка', 2, 90000, TO_DATE('2024-02-05', 'YYYY-MM-DD'), TO_DATE('2024-02-12', 'YYYY-MM-DD'));
INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Париж: test', 2, 80000, TO_DATE('2024-02-05', 'YYYY-MM-DD'), TO_DATE('2024-02-12', 'YYYY-MM-DD'));

INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Сафари в Африке', 3, 1800.00, TO_DATE('2024-08-01', 'YYYY-MM-DD'), TO_DATE('2024-08-15', 'YYYY-MM-DD'));

INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Антарктида: Полет на край света', 4, 5000.00, TO_DATE('2024-09-05', 'YYYY-MM-DD'), TO_DATE('2024-09-15', 'YYYY-MM-DD'));

INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES (seq_Employees.NEXTVAL, 'Александр', 'Смирнов', '+8005553535', 1400.00, 'Менеджер');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES (seq_Employees.NEXTVAL, 'Елена', 'Кузнецова', '+8005552323', 1300.00, 'Менеджер');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES (seq_Employees.NEXTVAL, 'Максим', 'Григорьев', '+8005554444', 1100.00, 'Менеджер');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES (seq_Employees.NEXTVAL, 'Светлана', 'Федорова', '+8005551234', 1200.00, 'Менеджер');

INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES (seq_Clients.NEXTVAL, 'Иван', 'Васильев', '+79112223344', 'ivan.vasiliy@example.com', 'AA1234567');
INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES (seq_Clients.NEXTVAL, 'Ольга', 'Сидорова', '+79123334455', 'olga.sidorova@example.com', 'BB1234567');
INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES (seq_Clients.NEXTVAL, 'Андрей', 'Козлов', '+79134445566', 'andrey.kozlov@example.com', 'CC1234567');
INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES (seq_Clients.NEXTVAL, 'Марина', 'Тимофеева', '+79145556677', 'marina.timofeeva@example.com', 'DD1234567');

-- Дополнительные продажи в таблицу Sales
-- Сотрудник 1 (Александр Смирнов)
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 1, TO_DATE('2024-01-15', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 1, 2, TO_DATE('2024-01-20', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 1, 3, TO_DATE('2024-02-10', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 4, 1, 4, TO_DATE('2024-02-15', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 2, TO_DATE('2024-03-01', 'YYYY-MM-DD'));

-- Сотрудник 2 (Елена Кузнецова)
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 2, 1, TO_DATE('2024-01-12', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 2, 3, TO_DATE('2024-02-05', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 4, 2, 4, TO_DATE('2024-02-25', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 2, 2, TO_DATE('2024-03-10', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 2, 1, TO_DATE('2024-03-18', 'YYYY-MM-DD'));

-- Сотрудник 3 (Максим Григорьев)
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 3, 3, TO_DATE('2024-01-30', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 4, 3, 4, TO_DATE('2024-02-05', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 3, 1, TO_DATE('2024-02-22', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 3, 2, TO_DATE('2024-03-05', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 4, 3, 3, TO_DATE('2024-03-20', 'YYYY-MM-DD'));

-- Сотрудник 4 (Светлана Федорова)
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 4, 2, TO_DATE('2024-01-25', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 4, 3, TO_DATE('2024-02-03', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 4, 4, 4, TO_DATE('2024-02-28', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 4, 1, TO_DATE('2024-03-03', 'YYYY-MM-DD'));
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 4, 2, TO_DATE('2024-03-12', 'YYYY-MM-DD'));

-- зависимость зарплаты для каждого сотрудника на следующий год помесячно, 
--учитывая процент суммарной стоимости оформленных туров по сравнению с другими сотрудниками.
--подзапросик
    SELECT 
        E.EmployeeId,
        E.Name || ' ' || E.SecondName AS EmployeeName,
        E.Salary AS BaseSalary,
        SUM(T.Price) AS TotalSales,
        SUM(SUM(T.Price)) OVER () AS TotalCompanySales,
        ROUND((SUM(T.Price) / SUM(SUM(T.Price)) OVER ()) * 100, 2) AS SalesPercentage
    FROM Sales S
    JOIN Employees E ON S.EmployeeId = E.EmployeeId
    JOIN Tours T ON S.TourId = T.TourId
    GROUP BY E.EmployeeId, E.Name, E.SecondName, E.Salary

--модэл
WITH SalesData AS (
    SELECT 
        E.EmployeeId,
        E.Name || ' ' || E.SecondName AS EmployeeName,
        E.Salary AS BaseSalary,
        SUM(T.Price) AS TotalSales,
        SUM(SUM(T.Price)) OVER () AS TotalCompanySales,
        ROUND((SUM(T.Price) / SUM(SUM(T.Price)) OVER ()) * 100, 2) AS SalesPercentage
    FROM Sales S
    JOIN Employees E ON S.EmployeeId = E.EmployeeId
    JOIN Tours T ON S.TourId = T.TourId
    GROUP BY E.EmployeeId, E.Name, E.SecondName, E.Salary
)
SELECT *
FROM SalesData
MODEL
    DIMENSION BY (EmployeeId)
    MEASURES (EmployeeName, BaseSalary, TotalSales, TotalCompanySales, SalesPercentage, 0 AS ProjectedSalaryNextYear)
    RULES (
        ProjectedSalaryNextYear[ANY] = BaseSalary[cv()] + (BaseSalary[cv()] * SalesPercentage[cv()] / 100)
    )
ORDER BY EmployeeId;
