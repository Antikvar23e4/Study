USE lab04QGIS;

-- 6.  Определите тип пространственных данных во всех таблицах
-- Эти данные описывают местоположение объектов в пространстве и могут быть использованы для моделирования и анализа географических и пространственных явлений.
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo'
--
-- 7.  Определите SRID - идентификатор системы координат
-- Примеры SRID включают SRID 4326, который обозначает систему координат WGS 84 (широта/долгота), который используется для веб-карт в проекции Web Mercator.
SELECT srid FROM dbo.geometry_columns

-- 8.  Определите атрибутивные столбцы
-- содержат информацию об атрибутах (характеристиках) географических объектов
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo' AND DATA_TYPE != 'geometry'

-- 9.  Верните описания пространственных объектов в формате WKT
--  текстовый формат для представления геометрических объектов в пространстве
SELECT geom.STAsText() AS WKT_Description
FROM myPackage

-- 10.1.  Нахождение пересечения пространственных объектов;
-- Определение области, общей для двух или более пространственных объектов.
SELECT obj1.geom.STIntersection(obj2.geom) AS Intersection
FROM myPackage obj1, myPackage obj2
WHERE obj1.qgs_fid = 20 AND obj2.qgs_fid = 20

SELECT obj1.geom.STIntersection(obj2.geom) AS Intersection
FROM myPackage obj1, myPackage obj2
WHERE obj1.qgs_fid = 11 AND obj2.qgs_fid = 8

SELECT obj1.geom.STIntersection(obj2.geom) AS Intersection
FROM myPackage obj1, myPackage obj2
WHERE obj1.qgs_fid = 3 AND obj2.qgs_fid = 5

-- 10.2.  Нахождение координат вершин пространственного объектов
SELECT geom.STPointN(1).ToString() AS Coordinates
FROM myPackage
WHERE qgs_fid = 7

-- 10.3  Нахождение площади пространственных объектов;
-- Площадь (Area): Измерение площади замкнутых объектов, таких как полигоны.
SELECT geom.STArea() AS ObjectArea
FROM myPackage
WHERE qgs_fid = 7

-- 11.  Создайте пространственный объект в виде точки (1) /линии (2) /полигона (3).
-- точка
DECLARE @pointGeometry GEOMETRY;
SET @pointGeometry = GEOMETRY::STGeomFromText('POINT(30 30)', 4326);

SELECT @pointGeometry AS PointGeometry;

-- линия
DECLARE @lineGeometry GEOMETRY;
SET @lineGeometry = GEOMETRY::STGeomFromText('LINESTRING(70 15, 5 27, 29 29)', 4326);

SELECT @lineGeometry AS LineGeometry;


-- полигон
DECLARE @polygonGeometry GEOMETRY;
SET @polygonGeometry = GEOMETRY::STGeomFromText('POLYGON((15 10, 57 57, 7 7, 17 1, 15 10))', 4326);

SELECT @polygonGeometry AS PolygonGeometry;


-- 12.  Найдите, в какие пространственные объекты попадают созданные вами объекты

-- точка и полигон

DECLARE @point GEOMETRY = GEOMETRY::STGeomFromText('POINT(30 30)', 4326);
SELECT * FROM myPackage WHERE geom.STContains(@point) = 1;

-- прямая и полигон
DECLARE @line GEOMETRY = GEOMETRY::STGeomFromText('LINESTRING(37 -17, 27 -17, 27 -17)', 4326);
SELECT * FROM myPackage WHERE geom.STContains(@line) = 1;

DECLARE @polygon GEOMETRY = GEOMETRY::STGeomFromText('POLYGON((25 -15, 25 -14, 26 -10, 25 -15))', 4326);
SELECT * FROM myPackage WHERE geom.STContains(@polygon) = 1;
--13.	Продемонстрируйте индексирование пространственных объектов.
CREATE SPATIAL INDEX index777777777777777777777777
ON [dbo].[geometry_columns] ([geom])
USING GEOMETRY_GRID
WITH (GRIDS = (LEVEL_1 = MEDIUM, LEVEL_2 = MEDIUM, LEVEL_3 = MEDIUM, LEVEL_4 = MEDIUM), BOUNDING_BOX = (0, 0, 50, 50));

DECLARE @searchPoint GEOMETRY;
SET @searchPoint = GEOMETRY::STGeomFromText('POINT(30 30)', 4326);

SELECT TOP 1 *
FROM [dbo].[geometry_columns] WITH(INDEX(SpatialIndex_new))
WHERE [geom].STIntersects(@searchPoint.STBuffer(5)) = 1;

INSERT INTO [dbo].[geometry_columns]
VALUES
    ('QGIS_LAB2','dbo','myPackage1','geom1',2,4326,'MULTIPOLYGON',GEOMETRY::STGeomFromText('POINT(20 20)', 4326)),
    ('QGIS_LAB3','dbo','myPackage2','geom2',2,4326,'MULTIPOLYGON',GEOMETRY::STGeomFromText('POLYGON((70 70, 70 70, 70 37, 40 30, 30 30))', 4326)),
    ('QGIS_LAB4','dbo','myPackage3','geom3',2,4326,'MULTIPOLYGON',GEOMETRY::STGeomFromText('LINESTRING(10 10, 15 15, 20 20)', 4326));
	UPDATE STATISTICS [dbo].[geometry_columns] WITH FULLSCAN;

--14.	Разработайте хранимую процедуру, которая принимает координаты точки и возвращает пространственный объект, в который эта точка попадает.
CREATE OR ALTER PROCEDURE GetGeometryFromPoint
    @latitude FLOAT,
    @longitude FLOAT,
    @resultGeometry GEOMETRY OUTPUT
AS
BEGIN
    DECLARE @point GEOMETRY = GEOMETRY::STGeomFromText('POINT(' + CAST(@longitude AS NVARCHAR(20)) + ' ' + CAST(@latitude AS NVARCHAR(20)) + ')', 4326);
    SET @resultGeometry = (SELECT TOP 1 geom FROM myPackage WHERE geom.STContains(@point) = 1);
END;

DECLARE @latitude FLOAT = 30.0;
DECLARE @longitude FLOAT = 30.0;
DECLARE @result GEOMETRY;

EXEC GetGeometryFromPoint @latitude, @longitude, @result OUTPUT;
select @result; 

-- @result теперь содержит объект GEOMETRY
SELECT @result AS PointGeometry;
