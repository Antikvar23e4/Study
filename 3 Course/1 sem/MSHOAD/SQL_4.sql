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
  (NEXT VALUE FOR seq_Route, 'Культурный тур по Москве', 'Экскурсия по главным достопримечательностям Москвы', 'Россия'),
  (NEXT VALUE FOR seq_Route, 'Золотое кольцо', 'Исторические города Центральной России', 'Россия'),
  (NEXT VALUE FOR seq_Route, 'Санкт-Петербургские музеи', 'Посещение музеев и дворцов Санкт-Петербурга', 'Россия');


INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES
  (NEXT VALUE FOR seq_Attractions, 'Красная площадь', 'Главная площадь Москвы', 1, 'Площадь'),
  (NEXT VALUE FOR seq_Attractions, 'Третьяковская галерея', 'Музей русского искусства', 1, 'Музей'),
  (NEXT VALUE FOR seq_Attractions, 'Эрмитаж', 'Один из крупнейших музеев мира', 3, 'Музей'),
  (NEXT VALUE FOR seq_Attractions, 'Золотые ворота', 'Старинные ворота Владимира', 2, 'Архитектурная достопримечательность'),
  (NEXT VALUE FOR seq_Attractions, 'Исаакиевский собор', 'Крупнейший православный собор', 3, 'Собор'),
  (NEXT VALUE FOR seq_Attractions, 'Кремль', 'Исторический комплекс в центре Москвы', 1, 'Историческая достопримечательность'),
  (NEXT VALUE FOR seq_Attractions, 'Большой театр', 'Главный театр страны', 1, 'Театр'),
  (NEXT VALUE FOR seq_Attractions, 'Петергоф', 'Знаменитые фонтаны и дворцы', 3, 'Дворец'),
  (NEXT VALUE FOR seq_Attractions, 'Невский проспект', 'Главная улица Санкт-Петербурга', 3, 'Улица'),
  (NEXT VALUE FOR seq_Attractions, 'Кунсткамера', 'Первый музей России в Санкт-Петербурге', 3, 'Музей'),
  (NEXT VALUE FOR seq_Attractions, 'Государственный Русский музей', 'Крупнейший музей русского искусства', 3, 'Музей'),
  (NEXT VALUE FOR seq_Attractions, 'Площадь Суворова', 'Одна из исторических площадей Москвы', 1, 'Площадь'),
  (NEXT VALUE FOR seq_Attractions, 'Собор Василия Блаженного', 'Известный собор в Москве', 1, 'Собор'),
  (NEXT VALUE FOR seq_Attractions, 'Санкт-Петербургский зоопарк', 'Первый зоопарк в России', 3, 'Зоопарк'),
  (NEXT VALUE FOR seq_Attractions, 'Московский зоопарк', 'Один из старейших зоопарков России', 1, 'Зоопарк'),
  (NEXT VALUE FOR seq_Attractions, 'Казанский собор', 'Известный собор в Санкт-Петербурге', 3, 'Собор'),
  (NEXT VALUE FOR seq_Attractions, 'Таврический сад', 'Исторический сад в Санкт-Петербурге', 3, 'Сад'),
  (NEXT VALUE FOR seq_Attractions, 'Парк Горького', 'Крупный городской парк в Москве', 1, 'Парк'),
  (NEXT VALUE FOR seq_Attractions, 'Третьяковская галерея', 'Музей русского искусства', 1, 'Музей');


INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES
  (NEXT VALUE FOR seq_Tours, 'Московский культурный маршрут', 1, 50000, '2024-01-10', '2024-01-15'),
  (NEXT VALUE FOR seq_Tours, 'Исторический тур по Золотому кольцу', 2, 45000, '2024-02-05', '2024-02-10'),
  (NEXT VALUE FOR seq_Tours, 'Музейный тур по Петербургу', 3, 60000, '2024-03-12', '2024-03-17');


  INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES
  (NEXT VALUE FOR seq_Employees, 'Алексей', 'Иванов', '+79251234567', 70000, 'Менеджер по продажам'),
  (NEXT VALUE FOR seq_Employees, 'Мария', 'Петрова', '+79253456789', 75000, 'Консультант по туризму'),
  (NEXT VALUE FOR seq_Employees, 'Олег', 'Сидоров', '+79257654321', 80000, 'Администратор');


  INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES
  (NEXT VALUE FOR seq_Clients, 'Иван', 'Смирнов', '+79161234567', 'ivan.smirnov@example.com', '4500123456'),
  (NEXT VALUE FOR seq_Clients, 'Анна', 'Кузнецова', '+79163456789', 'anna.kuznetsova@example.com', '4500789123'),
  (NEXT VALUE FOR seq_Clients, 'Дмитрий', 'Волков', '+79167654321', 'dmitry.volkov@example.com', '4500567891');


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

-- Вычисление итогов предоставленных услуг помесячно, за квартал, за полгода, за год.
SELECT 
    YEAR(SaleData) AS Год_Продажи,
    MONTH(SaleData) AS Месяц_Продажи,
    CASE -- для определения квартала
        WHEN MONTH(SaleData) BETWEEN 1 AND 3 THEN 1
        WHEN MONTH(SaleData) BETWEEN 4 AND 6 THEN 2
        WHEN MONTH(SaleData) BETWEEN 7 AND 9 THEN 3
        ELSE 4
    END AS Квартал_Продажи,
    CASE 
        WHEN MONTH(SaleData) BETWEEN 1 AND 6 THEN 'H1'
        ELSE 'H2'
    END AS Полугодие,
    COUNT(SaleId) OVER (PARTITION BY YEAR(SaleData), MONTH(SaleData)) AS Всего_Продаж,
    SUM(Tours.Price) OVER (PARTITION BY YEAR(SaleData), MONTH(SaleData)) AS Общая_Выручка
FROM Sales
JOIN Tours ON Sales.TourId = Tours.TourId
ORDER BY Год_Продажи, Месяц_Продажи;


-- Вычисление итогов предоставленных услуг за определенный период: объем услуг; сравнение их с общим объемом услуг (в %); сравнение с максимальным объемом услуг(в %).
DECLARE @StartDate DATE = '2023-01-01'; 
DECLARE @EndDate DATE = '2024-12-31';  
WITH ServiceVolume AS (
    SELECT 
        COUNT(SaleId) AS Объем_Продаж
    FROM Sales
    WHERE SaleData BETWEEN @StartDate AND @EndDate
),
TotalVolume AS (
    SELECT 
        COUNT(SaleId) AS Общий_Объем
    FROM Sales
),
MaxVolume AS (
    SELECT 
        COUNT(SaleId) AS Максимальный_Объем
    FROM Sales
    WHERE SaleData = (SELECT SaleData 
                      FROM Sales 
                      GROUP BY SaleData 
                      ORDER BY COUNT(SaleId) DESC 
                      OFFSET 0 ROWS FETCH NEXT 1 ROWS ONLY)  -- дата с максимальным количеством продаж
)
SELECT 
    SV.Объем_Продаж,
    CAST(SV.Объем_Продаж * 100.0 / TV.Общий_Объем AS DECIMAL(10, 2)) AS Процент_От_Общего_Объема,  -- Процент от общего объема
    CAST(SV.Объем_Продаж * 100.0 / MV.Максимальный_Объем AS DECIMAL(10, 2)) AS Процент_От_Максимального_Объема  -- Процент от максимального объема
FROM ServiceVolume SV, TotalVolume TV, MaxVolume MV;



-- Продемонстрируйте применение функции ранжирования ROW_NUMBER() для разбиения результатов запроса на страницы (по 20 строк на каждую страницу).
DECLARE @PageNumber INT = 2;  -- изменить номер страницы
DECLARE @RowsPerPage INT = 20; 
;WITH PaginatedSales AS (
    SELECT 
        *,
        ROW_NUMBER() OVER (ORDER BY SaleData DESC) AS RowNum  -- присваиваем номер строки
    FROM Sales
)
SELECT *
FROM PaginatedSales
WHERE RowNum BETWEEN (@PageNumber - 1) * @RowsPerPage + 1 AND @PageNumber * @RowsPerPage;  -- выбираем строки для нужной страницы




-- Продемонстрируйте применение функции ранжирования ROW_NUMBER() для удаления дубликатов.
WITH RankedSales AS (
    SELECT 
        *,
        ROW_NUMBER() OVER (PARTITION BY TourId, EmployeeId, ClientId ORDER BY SaleId) AS RowNum  -- нумеруем дубликаты
    FROM Sales
)
DELETE FROM RankedSales 
WHERE RowNum > 1;  -- удаляем дубликаты, оставляя только первое вхождение



-- Вернуть для каждого клиента – сколько раз посетил 6 самых посещаемых стран.
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
    Clients.Name AS Клиент,
    Clients.SecondName AS Фамилия,
    CV.Country AS Страна,
    CV.VisitCount AS Количество_Посещений
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


-- Какой маршрут включает наибольшее число достопримечательностей определенного вида? Вернуть для всех видов.
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
