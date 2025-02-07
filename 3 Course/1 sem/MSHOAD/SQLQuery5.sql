use a;
select * from geomdata

--���������� ��� ���������������� ������ �� ���� ��������.
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
  WHERE DATA_TYPE IN ('geometry', 'point', 'linestring', 'polygon', 'multipoint', 'multilinestring', 'multipolygon', 'geometrycollection');

--���������� SRID.
SELECT srid FROM dbo.geometry_columns
--4326 � ��� ����������� ������� ��������� WGS 84 (������������, ��������, � GPS)

--���������� ������������ �������.(������� ������� ���� ������, ������� �������� ���������� � �������������� ��������)
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo' AND DATA_TYPE != 'geometry'

--������� �������� ���������������� �������� � ������� WKT(��������� ������ ��� ������������� �������������� �������� � ������������).
SELECT geom.STAsText() AS WKT_Description
FROM geomdata

--���������� ����������� ���������������� ��������;
SELECT obj1.geom.STIntersection(obj2.geom) AS Intersection
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 20 AND obj2.id = 21;

--���������� ����������� ���������������� ��������;
SELECT obj1.geom.STUnion(obj2.geom) AS UnionResult
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 20 AND obj2.id = 21;

--���������� ����������� ���������������� ��������; ���������� 1 (������), ���� ������ obj1.geom ��������� ������ obj2.geom
SELECT obj1.geom.STWithin(obj2.geom) AS IsWithin
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 17 AND obj2.id = 2;

--�������� ���� �� ������ ����������� � ���� �� �� �����  ����� ��������
SELECT 
    obj1.id AS OuterObjectID, 
    obj1.name AS OuterObjectName,
    obj2.id AS InnerObjectID, 
    obj2.name AS InnerObjectName
FROM geomdata obj1
JOIN geomdata obj2
  ON obj1.geom.STWithin(obj2.geom) = 1
WHERE obj1.id != obj2.id;

--��������� ����������������� �������;
--STSimplify �� ���������� � SQL Server, � ��� ���������� ��������� ����� ������������ ������� ����������� ��� ����������.
--�������,  ������ ����� ������ ��������� �� ��������� ����������. ��������� ������������� ��������, ����� ��������� ��������� �������.
SELECT geom.STBuffer(-0.01) AS SimplifiedGeom
FROM geomdata
WHERE id = 20;

--���������� ��������� ������ ����������������� ��������;
SELECT geom.STPointN(1).ToString() AS Coordinates
FROM geomdata
WHERE id = 20;

--���������� ����������� ���������������� ��������; 0 � �����, 1 � �����, 2 � �������.
SELECT geom.STDimension() AS Dimension
FROM geomdata
WHERE id = 20;

--���������� ����� � ������� ���������������� ��������;
SELECT id, name, 
    geom.STLength() AS Length, 
    geom.STArea() AS Area
FROM geomdata;

--���������� ���������� ����� ����������������� ���������;
SELECT obj1.geom.STDistance(obj2.geom) AS Distance
FROM geomdata obj1, geomdata obj2
WHERE obj1.id = 1 AND obj2.id = 2;

--�������� ���������������� ������ � ���� ����� (1) /����� (2) /�������� (3).
DECLARE @point geometry = geometry::STGeomFromText('POINT(10 20)', 4326);
SELECT @point AS Point;

DECLARE @line geometry = geometry::STGeomFromText('LINESTRING(10 20, 15 25, 20 30)', 4326);
SELECT @line AS Line;

DECLARE @polygon geometry = geometry::STGeomFromText('POLYGON((10 20, 15 25, 20 20, 10 20))', 4326);
SELECT @polygon AS Polygon;

--�������, � ����� ���������������� ������� �������� ��������� ���� �������.
-- ����� ��������, � ������� �������� �����
DECLARE @point geometry = geometry::STGeomFromText('POINT(10 20)', 4326);
SELECT id, name
FROM geomdata
WHERE geom.STContains(@point) = 1;  -- ���������, �������� �� ������� �����

