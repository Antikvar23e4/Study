--LAB4
USE TourAgency;

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
ALTER TABLE Attractions
ADD AttractionType NVARCHAR(100);  

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

CREATE SEQUENCE seq_Route AS INT START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Attractions AS INT START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Tours AS INT START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Employees AS INT START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Clients AS INT START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Sales AS INT START WITH 1 INCREMENT BY 1;


INSERT INTO Route (RouteID, Name, Description, Country)
VALUES 
  (NEXT VALUE FOR seq_Route, '���������� ��� �� ������', '��������� �� ������� ���������������������� ������', '������'),
  (NEXT VALUE FOR seq_Route, '������� ������', '������������ ������ ����������� ������', '������'),
  (NEXT VALUE FOR seq_Route, '�����-������������� �����', '��������� ������ � ������� �����-����������', '������');


INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES
  (NEXT VALUE FOR seq_Attractions, '������� �������', '������� ������� ������', 1, '�������'),
  (NEXT VALUE FOR seq_Attractions, '������������� �������', '����� �������� ���������', 1, '�����'),
  (NEXT VALUE FOR seq_Attractions, '�������', '���� �� ���������� ������ ����', 3, '�����'),
  (NEXT VALUE FOR seq_Attractions, '������� ������', '��������� ������ ���������', 2, '������������� ���������������������'),
  (NEXT VALUE FOR seq_Attractions, '������������ �����', '���������� ������������ �����', 3, '�����'),
  (NEXT VALUE FOR seq_Attractions, '������', '������������ �������� � ������ ������', 1, '������������ ���������������������'),
  (NEXT VALUE FOR seq_Attractions, '������� �����', '������� ����� ������', 1, '�����'),
  (NEXT VALUE FOR seq_Attractions, '��������', '���������� ������� � ������', 3, '������'),
  (NEXT VALUE FOR seq_Attractions, '������� ��������', '������� ����� �����-����������', 3, '�����'),
  (NEXT VALUE FOR seq_Attractions, '�����������', '������ ����� ������ � �����-����������', 3, '�����'),
  (NEXT VALUE FOR seq_Attractions, '��������������� ������� �����', '���������� ����� �������� ���������', 3, '�����'),
  (NEXT VALUE FOR seq_Attractions, '������� ��������', '���� �� ������������ �������� ������', 1, '�������'),
  (NEXT VALUE FOR seq_Attractions, '����� ������� ����������', '��������� ����� � ������', 1, '�����'),
  (NEXT VALUE FOR seq_Attractions, '�����-������������� �������', '������ ������� � ������', 3, '�������'),
  (NEXT VALUE FOR seq_Attractions, '���������� �������', '���� �� ��������� ��������� ������', 1, '�������'),
  (NEXT VALUE FOR seq_Attractions, '��������� �����', '��������� ����� � �����-����������', 3, '�����'),
  (NEXT VALUE FOR seq_Attractions, '����������� ���', '������������ ��� � �����-����������', 3, '���'),
  (NEXT VALUE FOR seq_Attractions, '���� ��������', '������� ��������� ���� � ������', 1, '����'),
  (NEXT VALUE FOR seq_Attractions, '������������� �������', '����� �������� ���������', 1, '�����');


INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES
  (NEXT VALUE FOR seq_Tours, '���������� ���������� �������', 1, 50000, '2024-01-10', '2024-01-15'),
  (NEXT VALUE FOR seq_Tours, '������������ ��� �� �������� ������', 2, 45000, '2024-02-05', '2024-02-10'),
  (NEXT VALUE FOR seq_Tours, '�������� ��� �� ����������', 3, 60000, '2024-03-12', '2024-03-17');


  INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES
  (NEXT VALUE FOR seq_Employees, '�������', '������', '+79251234567', 70000, '�������� �� ��������'),
  (NEXT VALUE FOR seq_Employees, '�����', '�������', '+79253456789', 75000, '����������� �� �������'),
  (NEXT VALUE FOR seq_Employees, '����', '�������', '+79257654321', 80000, '�������������');


  INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES
  (NEXT VALUE FOR seq_Clients, '����', '�������', '+79161234567', 'ivan.smirnov@example.com', '4500123456'),
  (NEXT VALUE FOR seq_Clients, '����', '���������', '+79163456789', 'anna.kuznetsova@example.com', '4500789123'),
  (NEXT VALUE FOR seq_Clients, '�������', '������', '+79167654321', 'dmitry.volkov@example.com', '4500567891');


  INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES
  (NEXT VALUE FOR seq_Sales, 1, 1, 1, '2024-01-05'),
  (NEXT VALUE FOR seq_Sales, 2, 2, 2, '2024-02-01'),
  (NEXT VALUE FOR seq_Sales, 3, 3, 3, '2024-03-10'),
  (NEXT VALUE FOR seq_Sales, 1, 1, 3, '2024-01-12'),
  (NEXT VALUE FOR seq_Sales, 3, 2, 1, '2024-03-13'),
  (NEXT VALUE FOR seq_Sales, 1, 1, 1, '2022-01-05'), 
  (NEXT VALUE FOR seq_Sales, 2, 2, 2, '2022-02-10'),  
  (NEXT VALUE FOR seq_Sales, 3, 3, 3, '2022-03-15'),  
  (NEXT VALUE FOR seq_Sales, 1, 1, 3, '2022-04-20'),  
  (NEXT VALUE FOR seq_Sales, 3, 2, 1, '2022-05-25'),  
  (NEXT VALUE FOR seq_Sales, 2, 1, 2, '2022-06-30'),  
  (NEXT VALUE FOR seq_Sales, 1, 2, 1, '2023-01-15'),  
  (NEXT VALUE FOR seq_Sales, 2, 2, 2, '2023-02-20'),  
  (NEXT VALUE FOR seq_Sales, 3, 3, 3, '2023-03-10'), 
  (NEXT VALUE FOR seq_Sales, 1, 1, 3, '2023-04-05'),  
  (NEXT VALUE FOR seq_Sales, 3, 2, 1, '2023-05-12'), 
  (NEXT VALUE FOR seq_Sales, 2, 1, 2, '2023-06-18'),  
  (NEXT VALUE FOR seq_Sales, 1, 2, 3, '2024-01-10'),  
  (NEXT VALUE FOR seq_Sales, 2, 1, 1, '2024-01-12'),  
  (NEXT VALUE FOR seq_Sales, 3, 2, 2, '2024-02-05'),  
  (NEXT VALUE FOR seq_Sales, 1, 1, 2, '2024-02-15'),  
  (NEXT VALUE FOR seq_Sales, 2, 3, 1, '2024-03-20'), 
  (NEXT VALUE FOR seq_Sales, 3, 2, 3, '2024-03-25'); 


SELECT * FROM Route;
SELECT * FROM Attractions;
SELECT * FROM Tours;
SELECT * FROM Employees;
SELECT * FROM Clients;
SELECT * FROM Sales;

SELECT * FROM View_ToursRoutesAttractions;
SELECT * FROM View_SalesInfo;

-- ���������� ������ ��������������� ����� ���������, �� �������, �� �������, �� ���.
SELECT 
    YEAR(SaleData) AS ���_�������,
    MONTH(SaleData) AS �����_�������,
    CASE -- ��� ����������� ��������
        WHEN MONTH(SaleData) BETWEEN 1 AND 3 THEN 1
        WHEN MONTH(SaleData) BETWEEN 4 AND 6 THEN 2
        WHEN MONTH(SaleData) BETWEEN 7 AND 9 THEN 3
        ELSE 4
    END AS �������_�������,
    CASE 
        WHEN MONTH(SaleData) BETWEEN 1 AND 6 THEN 'H1'
        ELSE 'H2'
    END AS ���������,
    COUNT(SaleId) OVER (PARTITION BY YEAR(SaleData), MONTH(SaleData)) AS �����_������,
    SUM(Tours.Price) OVER (PARTITION BY YEAR(SaleData), MONTH(SaleData)) AS �����_�������
FROM Sales
JOIN Tours ON Sales.TourId = Tours.TourId
ORDER BY ���_�������, �����_�������;


-- ���������� ������ ��������������� ����� �� ������������ ������: ����� �����; ��������� �� � ����� ������� ����� (� %); ��������� � ������������ ������� �����(� %).
DECLARE @StartDate DATE = '2023-01-01'; 
DECLARE @EndDate DATE = '2024-12-31';  
WITH ServiceVolume AS (
    SELECT 
        COUNT(SaleId) AS �����_������
    FROM Sales
    WHERE SaleData BETWEEN @StartDate AND @EndDate
),
TotalVolume AS (
    SELECT 
        COUNT(SaleId) AS �����_�����
    FROM Sales
),
MaxVolume AS (
    SELECT 
        COUNT(SaleId) AS ������������_�����
    FROM Sales
    WHERE SaleData = (SELECT SaleData 
                      FROM Sales 
                      GROUP BY SaleData 
                      ORDER BY COUNT(SaleId) DESC 
                      OFFSET 0 ROWS FETCH NEXT 1 ROWS ONLY)  -- ���� � ������������ ����������� ������
)
SELECT 
    SV.�����_������,
    CAST(SV.�����_������ * 100.0 / TV.�����_����� AS DECIMAL(10, 2)) AS �������_��_������_������,  -- ������� �� ������ ������
    CAST(SV.�����_������ * 100.0 / MV.������������_����� AS DECIMAL(10, 2)) AS �������_��_�������������_������  -- ������� �� ������������� ������
FROM ServiceVolume SV, TotalVolume TV, MaxVolume MV;



-- ����������������� ���������� ������� ������������ ROW_NUMBER() ��� ��������� ����������� ������� �� �������� (�� 20 ����� �� ������ ��������).
DECLARE @PageNumber INT = 2;  -- �������� ����� ��������
DECLARE @RowsPerPage INT = 20; 
;WITH PaginatedSales AS (
    SELECT 
        *,
        ROW_NUMBER() OVER (ORDER BY SaleData DESC) AS RowNum  -- ����������� ����� ������
    FROM Sales
)
SELECT *
FROM PaginatedSales
WHERE RowNum BETWEEN (@PageNumber - 1) * @RowsPerPage + 1 AND @PageNumber * @RowsPerPage;  -- �������� ������ ��� ������ ��������




-- ����������������� ���������� ������� ������������ ROW_NUMBER() ��� �������� ����������.
WITH RankedSales AS (
    SELECT 
        *,
        ROW_NUMBER() OVER (PARTITION BY TourId, EmployeeId, ClientId ORDER BY SaleId) AS RowNum  -- �������� ���������
    FROM Sales
)
DELETE FROM RankedSales 
WHERE RowNum > 1;  -- ������� ���������, �������� ������ ������ ���������



-- ������� ��� ������� ������� � ������� ��� ������� 6 ����� ���������� �����.
WITH CountryVisits AS (
    SELECT 
        Route.Country,
        Sales.ClientId,
        COUNT(SaleId) AS VisitCount,
        ROW_NUMBER() OVER (PARTITION BY Route.Country ORDER BY COUNT(SaleId) DESC) AS CountryRank
    FROM Sales
    JOIN Tours ON Sales.TourId = Tours.TourId
    JOIN Route ON Tours.RouteId = Route.RouteID
    GROUP BY Route.Country, Sales.ClientId
)
SELECT 
    Clients.Name AS ������,
    Clients.SecondName AS �������,
    CV.Country AS ������,
    CV.VisitCount AS ����������_���������
FROM CountryVisits CV
JOIN Clients ON CV.ClientId = Clients.ClientId
WHERE CV.Country IN (
    SELECT Country
    FROM (
        SELECT 
            Country,
            RANK() OVER (ORDER BY SUM(VisitCount) DESC) AS CountryRank
        FROM CountryVisits
        GROUP BY Country
    ) AS RankedCountries
    WHERE CountryRank <= 6
)
ORDER BY Clients.Name, CV.Country;


-- ����� ������� �������� ���������� ����� ���������������������� ������������� ����? ������� ��� ���� �����.
	WITH AttractionCounts AS (
    SELECT 
        r.Name AS RouteName,
        a.AttractionType,
        COUNT(a.AttractionId) AS CountOfAttractions,
        MAX(COUNT(a.AttractionId)) OVER (PARTITION BY a.AttractionType) AS MaxCount
    FROM 
        Route r
    JOIN 
        Attractions a ON r.RouteID = a.RouteId
    GROUP BY r.Name, a.AttractionType
)
SELECT 
    ac.AttractionType,
    ac.RouteName,
    ac.CountOfAttractions
FROM 
    AttractionCounts ac
WHERE 
    ac.CountOfAttractions = ac.MaxCount
ORDER BY ac.AttractionType;
