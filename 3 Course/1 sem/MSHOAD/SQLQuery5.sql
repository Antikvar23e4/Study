use a;
select * from geomdata

--Определите тип пространственных данных во всех таблицах.
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
  WHERE DATA_TYPE IN ('geometry', 'point', 'linestring', 'polygon', 'multipoint', 'multilinestring', 'multipolygon', 'geometrycollection');

--Определите SRID.
SELECT srid FROM dbo.geometry_columns
--4326 — это стандартная система координат WGS 84 (используется, например, в GPS)

--Определите атрибутивные столбцы.(столбцы таблицы базы данных, которые содержат информацию о геометрических объектах)
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo' AND DATA_TYPE != 'geometry'

--Верните описания пространственных объектов в формате WKT(текстовый формат для представления геометрических объектов в пространстве).
SELECT geom.STAsText() AS WKT_Description
FROM geomdata

--Нахождение пересечения пространственных объектов;
SELECT obj1.geom.STIntersection(obj2.geom) AS Intersection
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 20 AND obj2.id = 21;

--Нахождение объединения пространственных объектов;
SELECT obj1.geom.STUnion(obj2.geom) AS UnionResult
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 20 AND obj2.id = 21;

--Нахождение вложенности пространственных объектов; Возвращает 1 (истина), если объект obj1.geom находится внутри obj2.geom
SELECT obj1.geom.STWithin(obj2.geom) AS IsWithin
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 17 AND obj2.id = 2;

--Проверка есть ли вообще вложенности и если да то вывод  таких объектов
SELECT 
    obj1.id AS OuterObjectID, 
    obj1.name AS OuterObjectName,
    obj2.id AS InnerObjectID, 
    obj2.name AS InnerObjectName
FROM geomdata obj1
JOIN geomdata obj2
  ON obj1.geom.STWithin(obj2.geom) = 1
WHERE obj1.id != obj2.id;

--Упрощение пространственного объекта;
--STSimplify не существует в SQL Server, и для настоящего упрощения нужно использовать внешние инструменты или библиотеки.
--Функция,  создаёт буфер вокруг геометрии на указанное расстояние. Используя отрицательное значение, можно уменьшить сложность объекта.
SELECT geom.STBuffer(-0.01) AS SimplifiedGeom
FROM geomdata
WHERE id = 20;

--Нахождение координат вершин пространственного объектов;
SELECT geom.STPointN(1).ToString() AS Coordinates
FROM geomdata
WHERE id = 20;

--Нахождение размерности пространственных объектов; 0 — точка, 1 — линия, 2 — полигон.
SELECT geom.STDimension() AS Dimension
FROM geomdata
WHERE id = 20;

--Нахождение длины и площади пространственных объектов;
SELECT id, name, 
    geom.STLength() AS Length, 
    geom.STArea() AS Area
FROM geomdata;

--Нахождение расстояния между пространственными объектами;
SELECT obj1.geom.STDistance(obj2.geom) AS Distance
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 1 AND obj2.id = 2;

--Создайте пространственный объект в виде точки (1) /линии (2) /полигона (3).
DECLARE @point geometry = geometry::STGeomFromText('POINT(10 20)', 4326);
SELECT @point AS Point;

DECLARE @line geometry = geometry::STGeomFromText('LINESTRING(10 20, 15 25, 20 30)', 4326);
SELECT @line AS Line;

DECLARE @polygon geometry = geometry::STGeomFromText('POLYGON((10 20, 15 25, 20 20, 10 20))', 4326);
SELECT @polygon AS Polygon;

--Найдите, в какие пространственные объекты попадают созданные вами объекты.
-- Поиск объектов, в которые попадает точка
DECLARE @point geometry = geometry::STGeomFromText('POINT(10 20)', 4326);
SELECT id, name
FROM geomdata
WHERE geom.STContains(@point) = 1;  -- Проверяем, содержат ли объекты точку

