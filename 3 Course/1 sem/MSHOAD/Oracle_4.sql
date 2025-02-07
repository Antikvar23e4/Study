DELETE FROM Sales;
DELETE FROM Tours;
DELETE FROM Attractions;
DELETE FROM Clients;
DELETE FROM Employees;
DELETE FROM Route;


CREATE SEQUENCE seq_Route START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Attractions START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Tours START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Employees START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Clients START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE seq_Sales START WITH 1 INCREMENT BY 1;

ALTER TABLE Attractions
ADD AttractionType NVARCHAR2(100);

INSERT INTO Route (RouteID, Name, Description, Country)
VALUES (seq_Route.NEXTVAL, 'Культурный тур по Москве', 'Экскурсия по главным достопримечательностям Москвы', 'Россия');
INSERT INTO Route (RouteID, Name, Description, Country)
VALUES (seq_Route.NEXTVAL, 'Золотое кольцо', 'Исторические города Центральной России', 'Россия');
INSERT INTO Route (RouteID, Name, Description, Country)
VALUES (seq_Route.NEXTVAL, 'Санкт-Петербургские музеи', 'Посещение музеев и дворцов Санкт-Петербурга', 'Россия');
COMMIT;

INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Красная площадь', 'Главная площадь Москвы', 1, 'Площадь');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Третьяковская галерея', 'Музей русского искусства', 1, 'Музей');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Эрмитаж', 'Один из крупнейших музеев мира', 3, 'Музей');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Золотые ворота', 'Старинные ворота Владимира', 2, 'Архитектурная достопримечательность');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Исаакиевский собор', 'Крупнейший православный собор', 3, 'Собор');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Кремль', 'Исторический комплекс в центре Москвы', 1, 'Историческая достопримечательность');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Большой театр', 'Главный театр страны', 1, 'Театр');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Петергоф', 'Знаменитые фонтаны и дворцы', 3, 'Дворец');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Невский проспект', 'Главная улица Санкт-Петербурга', 3, 'Улица');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Кунсткамера', 'Первый музей России в Санкт-Петербурге', 3, 'Музей');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Государственный Русский музей', 'Крупнейший музей русского искусства', 3, 'Музей');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Площадь Суворова', 'Одна из исторических площадей Москвы', 1, 'Площадь');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Собор Василия Блаженного', 'Известный собор в Москве', 1, 'Собор');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Санкт-Петербургский зоопарк', 'Первый зоопарк в России', 3, 'Зоопарк');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Московский зоопарк', 'Один из старейших зоопарков России', 1, 'Зоопарк');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Казанский собор', 'Известный собор в Санкт-Петербурге', 3, 'Собор');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Таврический сад', 'Исторический сад в Санкт-Петербурге', 3, 'Сад');
INSERT INTO Attractions (AttractionId, Name, Description, RouteId, AttractionType)
VALUES (seq_Attractions.NEXTVAL, 'Парк Горького', 'Крупный городской парк в Москве', 1, 'Парк');
COMMIT;

INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Московский культурный маршрут', 1, 50000, DATE '2024-01-10', DATE '2024-01-15');
INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Исторический тур по Золотому кольцу', 2, 45000, DATE '2024-02-05', DATE '2024-02-10');
INSERT INTO Tours (TourId, Name, RouteId, Price, DepartureDate, ReturnDate)
VALUES (seq_Tours.NEXTVAL, 'Музейный тур по Петербургу', 3, 60000, DATE '2024-03-12', DATE '2024-03-17');
COMMIT;

INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES (seq_Employees.NEXTVAL, 'Алексей', 'Иванов', '+79251234567', 70000, 'Менеджер по продажам');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES (seq_Employees.NEXTVAL, 'Мария', 'Петрова', '+79253456789', 75000, 'Консультант по туризму');
INSERT INTO Employees (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job)
VALUES (seq_Employees.NEXTVAL, 'Олег', 'Сидоров', '+79257654321', 80000, 'Администратор');
COMMIT;

INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES (seq_Clients.NEXTVAL, 'Иван', 'Смирнов', '+79161234567', 'ivan.smirnov@example.com', '4500123456');
INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES (seq_Clients.NEXTVAL, 'Анна', 'Кузнецова', '+79163456789', 'anna.kuznetsova@example.com', '4500789123');
INSERT INTO Clients (ClientId, Name, SecondName, PhoneNumber, Email, Passport)
VALUES (seq_Clients.NEXTVAL, 'Дмитрий', 'Волков', '+79167654321', 'dmitry.volkov@example.com', '4500567891');
COMMIT;

INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 1, DATE '2024-01-05');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 2, 2, DATE '2024-02-01');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 3, 3, DATE '2024-03-10');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 3, DATE '2024-01-12');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 2, 1, DATE '2024-03-13');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 1, DATE '2022-01-05');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 2, 2, DATE '2022-02-10');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 3, 3, DATE '2022-03-15');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 3, DATE '2022-04-20');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 2, 1, DATE '2022-05-25');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 1, 2, DATE '2022-06-30');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 2, 1, DATE '2023-01-15');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 2, 2, DATE '2023-02-20');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 3, 3, DATE '2023-03-10');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 3, DATE '2023-04-05');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 2, 1, DATE '2023-05-12');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 1, 2, DATE '2023-06-18');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 2, 3, DATE '2024-01-10');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 1, 1, DATE '2024-01-12');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 2, 2, DATE '2024-02-05');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 1, 1, 2, DATE '2024-02-15');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 2, 3, 1, DATE '2024-03-20');
INSERT INTO Sales (SaleId, TourId, EmployeeId, ClientId, SaleData)
VALUES (seq_Sales.NEXTVAL, 3, 2, 3, DATE '2024-03-25');
COMMIT;



-- Вычисление итогов предоставленных услуг помесячно, за квартал, за полгода, за год.
SELECT 
    EXTRACT(YEAR FROM SaleData) AS Год_Продажи,
    EXTRACT(MONTH FROM SaleData) AS Месяц_Продажи,
    CASE 
        WHEN EXTRACT(MONTH FROM SaleData) BETWEEN 1 AND 3 THEN 1
        WHEN EXTRACT(MONTH FROM SaleData) BETWEEN 4 AND 6 THEN 2
        WHEN EXTRACT(MONTH FROM SaleData) BETWEEN 7 AND 9 THEN 3
        ELSE 4
    END AS Квартал_Продажи,
    CASE 
        WHEN EXTRACT(MONTH FROM SaleData) BETWEEN 1 AND 6 THEN 'H1'
        ELSE 'H2'
    END AS Полугодие,
    COUNT(SaleId) AS Всего_Продаж,
    SUM(Tours.Price) AS Общая_Выручка
FROM Sales
JOIN Tours ON Sales.TourId = Tours.TourId
GROUP BY 
    EXTRACT(YEAR FROM SaleData),
    EXTRACT(MONTH FROM SaleData)
ORDER BY  Год_Продажи, Месяц_Продажи;



-- Вычисление итогов предоставленных услуг за определенный период: объем услуг; сравнение их с общим объемом услуг (в %); сравнение с максимальным объемом услуг(в %).
WITH PeriodSales AS (
    SELECT 
        COUNT(S.TourId) AS VolumeServices,
        SUM(T.Price) AS TotalRevenue
    FROM 
        Sales S
    JOIN 
        Tours T ON S.TourId = T.TourId
    WHERE 
        S.SaleData BETWEEN TO_DATE('2022-11-01', 'YYYY-MM-DD') AND TO_DATE('2024-11-05', 'YYYY-MM-DD')
),
OverallSales AS (
    SELECT 
        COUNT(T.TourId) AS TotalTours,
        SUM(T.Price) AS OverallRevenue
    FROM 
        Tours T
),
MaxSales AS (
    SELECT 
        MAX(SaleCount) AS MaxVolume
    FROM (
        SELECT 
            COUNT(S.TourId) AS SaleCount
        FROM 
            Sales S
        GROUP BY S.TourId
    )
)
SELECT 
    PS.VolumeServices,
    ROUND((PS.VolumeServices / OS.TotalTours) * 100, 2) AS VolumePercentage,
    ROUND((PS.VolumeServices / MS.MaxVolume) * 100, 2) AS MaxVolumePercentage
FROM 
    PeriodSales PS,
    OverallSales OS,
    MaxSales MS;



--Вернуть для каждого клиента – сколько раз посетил 6 самых посещаемых стран.
WITH CountryVisits AS (
    SELECT 
        Route.Country,
        Sales.ClientId,
        COUNT(Sales.SaleId) AS VisitCount
    FROM 
        Sales
    JOIN 
        Tours ON Sales.TourId = Tours.TourId
    JOIN 
        Route ON Tours.RouteId = Route.RouteID
    GROUP BY  Route.Country, Sales.ClientId
),
RankedCountries AS (
    SELECT 
        Country,
        RANK() OVER (ORDER BY SUM(VisitCount) DESC) AS CountryRank
    FROM 
        CountryVisits
    GROUP BY  Country
)
SELECT 
    Clients.Name AS ClientName,      
    Clients.SecondName AS LastName,   
    CV.Country AS Country,            
    CV.VisitCount AS VisitCount      
FROM 
    CountryVisits CV
JOIN 
    Clients ON CV.ClientId = Clients.ClientId
WHERE 
    CV.Country IN (
        SELECT Country
        FROM RankedCountries
        WHERE CountryRank <= 6
    )
ORDER BY  Clients.Name, CV.Country;


-- Какой маршрут включает наибольшее число достопримечательностей определенного вида? Вернуть для всех видов.
WITH AttractionCounts AS (
    SELECT 
        r.Name AS RouteName,
        a.AttractionType,
        COUNT(a.AttractionId) AS CountOfAttractions
    FROM 
        Route r
    JOIN 
        Attractions a ON r.RouteID = a.RouteId
    GROUP BY  r.Name, a.AttractionType
),
MaxAttractionCounts AS (
    SELECT 
        AttractionType,
        MAX(CountOfAttractions) AS MaxCount
    FROM 
        AttractionCounts
    GROUP BY  AttractionType
)
SELECT 
    ac.AttractionType,
    ac.RouteName,
    ac.CountOfAttractions
FROM 
    AttractionCounts ac
JOIN 
    MaxAttractionCounts mac ON ac.AttractionType = mac.AttractionType AND ac.CountOfAttractions = mac.MaxCount
ORDER BY  ac.AttractionType, ac.RouteName;





















-- Продемонстрируйте применение функции ранжирования ROW_NUMBER() для разбиения результатов запроса на страницы (по 20 строк на каждую страницу).
-- Продемонстрируйте применение функции ранжирования ROW_NUMBER() для удаления дубликатов.\
