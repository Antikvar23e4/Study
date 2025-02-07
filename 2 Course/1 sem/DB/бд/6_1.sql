USE UNIVER
/*1,2 ������������ ���������� ���������� ������, ������ GROUP BY � ���������� �������. */
SELECT 
    AUDITORIUM_TYPENAME,
    MAX(AUDITORIUM_CAPACITY) AS [������������ ���������������],
    MIN(AUDITORIUM_CAPACITY) AS [����������� ���������������],
    AVG(AUDITORIUM_CAPACITY) AS [������� ���������������],
    COUNT(AUDITORIUM) AS [����� ���-�� ���������],
    SUM(AUDITORIUM_CAPACITY) AS [����� ��������������� ��������� ������� ����]
FROM 
    AUDITORIUM_TYPE
JOIN 
    AUDITORIUM A ON AUDITORIUM_TYPE.AUDITORIUM_TYPE = A.AUDITORIUM_TYPE
GROUP BY 
    AUDITORIUM_TYPENAME;

/*3 ������������ ��������� � ������ FROM, � ���������� ��������� GROUP BY � CASE. */
SELECT *
FROM (
    SELECT 
        CASE
            WHEN PROGRESS.NOTE IN (6, 7) THEN '6-7'
            WHEN PROGRESS.NOTE IN (8, 9) THEN '8-9'
            WHEN PROGRESS.NOTE IN (4, 5) THEN '4-5'
            WHEN PROGRESS.NOTE = 10 THEN '10'
        END AS [������],
        COUNT(*) AS [����������]
    FROM PROGRESS
    GROUP BY
        CASE
            WHEN PROGRESS.NOTE IN (6, 7) THEN '6-7'
            WHEN PROGRESS.NOTE IN (8, 9) THEN '8-9'
            WHEN PROGRESS.NOTE IN (4, 5) THEN '4-5'
            WHEN PROGRESS.NOTE = 10 THEN '10'
        END
) AS a
ORDER BY
    CASE a.������
        WHEN '6-7' THEN 2
        WHEN '8-9' THEN 3
        WHEN '4-5' THEN 1
        WHEN '10' THEN 4
    END;

/*4 ������������ ���������� ���������� ������, ���������� ������� AVG � �����-����� ������� CAST � ROUND*/
SELECT
    a.FACULTY, G.PROFESSION,
    (2014 - G.YEAR_FIRST) AS [����],
    ROUND(AVG(CAST(NOTE AS FLOAT(4))), 2) AS [������� ������]
FROM
    FACULTY a
    INNER JOIN GROUPS G ON a.FACULTY = G.FACULTY
    INNER JOIN STUDENT S ON G.IDGROUP = S.IDGROUP
    INNER JOIN PROGRESS P ON S.IDSTUDENT = P.IDSTUDENT
GROUP BY
    a.FACULTY, G.PROFESSION, G.YEAR_FIRST;

/*5 ������ ������ �� ����������� � ������ �� � ����*/
SELECT
    a.FACULTY, G.PROFESSION,
    (2014 - G.YEAR_FIRST) AS [����],
    ROUND(AVG(CAST(NOTE AS FLOAT(4))), 2) AS [������� ������]
FROM
    FACULTY a
    INNER JOIN GROUPS G ON a.FACULTY = G.FACULTY
    INNER JOIN STUDENT S ON G.IDGROUP = S.IDGROUP
    INNER JOIN PROGRESS P ON S.IDSTUDENT = P.IDSTUDENT AND P.SUBJECT IN ('����', '����')
GROUP BY
    a.FACULTY, G.PROFESSION, G.YEAR_FIRST;

/*6*/
SELECT
    GROUPS.PROFESSION, P.SUBJECT, AVG(NOTE) AS AVERAGE_NOTE
FROM
    GROUPS
    FULL JOIN STUDENT S ON GROUPS.IDGROUP = S.IDGROUP AND GROUPS.FACULTY = '���'
    FULL JOIN PROGRESS P ON S.IDSTUDENT = P.IDSTUDENT
GROUP BY
    P.SUBJECT,
    GROUPS.PROFESSION;

/*7 ������������ �����������, ������ HAVING, ����������*/
SELECT
    SUBJECT, COUNT(NOTE) AS [���-��]
FROM
    PROGRESS
WHERE
    NOTE IN (8, 9)
GROUP BY
    SUBJECT, NOTE;
