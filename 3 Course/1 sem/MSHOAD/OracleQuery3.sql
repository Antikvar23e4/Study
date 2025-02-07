CREATE TABLE Employees2 (
    EmployeeId NUMBER PRIMARY KEY,
    Name VARCHAR2(255) NOT NULL,
    SecondName VARCHAR2(255),
    PhoneNumber VARCHAR2(20),
    Salary NUMBER(10, 2),
    Job VARCHAR2(100),
    ManagerId NUMBER,
    FOREIGN KEY (ManagerId) REFERENCES Employees2(EmployeeId) ON DELETE SET NULL
);

INSERT INTO Employees2 (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job, ManagerId) VALUES 
(1, 'John', 'Smith', '555-1234', 5000.00, 'Руководитель компании', NULL);

INSERT INTO Employees2 (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job, ManagerId) VALUES 
(2, 'Alice', 'Johnson', '555-2345', 4000.00, 'Финансовый директор', 1);  -- менеджер - John (ID 1)

INSERT INTO Employees2 (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job, ManagerId) VALUES 
(3, 'Bob', 'Williams', '555-3456', 3500.00, 'Менеджер по продажам', 1);  -- John (ID 1)

INSERT INTO Employees2 (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job, ManagerId) VALUES 
(4, 'Carol', 'Taylor', '555-4567', 3000.00, 'Бухгалтер', 2);  -- Alice (ID 2)

INSERT INTO Employees2 (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job, ManagerId) VALUES 
(5, 'David', 'Brown', '555-5678', 2500.00, 'Торговый представитель', 3);  -- менеджер - Bob (ID 3)

INSERT INTO Employees2 (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job, ManagerId) VALUES 
(6, 'Eve', 'Davis', '555-6789', 2500.00, 'Торговый представитель', 3);  -- менеджер - Bob (ID 3)

SELECT * FROM Employees2;

--2
CREATE OR REPLACE PROCEDURE ShowSubordinates(p_ManagerId IN NUMBER) IS
BEGIN
    FOR rec IN (
        SELECT EmployeeId, 
               Name, 
               Job, 
               LEVEL AS HierarchyLevel,
               SYS_CONNECT_BY_PATH(EmployeeId, '/') AS HierarchyPath
        FROM Employees2
        START WITH EmployeeId = p_ManagerId
        CONNECT BY PRIOR EmployeeId = ManagerId
    ) LOOP
        DBMS_OUTPUT.PUT_LINE('Level ' || rec.HierarchyLevel || ': ' || rec.Name || ' (' || rec.Job || ') - Path: ' || rec.HierarchyPath);
    END LOOP;
END;

BEGIN
    ShowSubordinates(1); 
END;

--3

CREATE OR REPLACE PROCEDURE AddSubordinate(
    p_EmployeeId IN NUMBER,
    p_Name IN VARCHAR2,
    p_SecondName IN VARCHAR2,
    p_PhoneNumber IN VARCHAR2,
    p_Salary IN NUMBER,
    p_Job IN VARCHAR2,
    p_ManagerId IN NUMBER
) IS
BEGIN
    INSERT INTO Employees2 (EmployeeId, Name, SecondName, PhoneNumber, Salary, Job, ManagerId)
    VALUES (p_EmployeeId, p_Name, p_SecondName, p_PhoneNumber, p_Salary, p_Job, p_ManagerId);
    
    COMMIT; 
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
        DBMS_OUTPUT.PUT_LINE('Ошибка: Указанный EmployeeId уже существует.');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLERRM);
END;


BEGIN
    AddSubordinate(
        7,                          
        'Frank',                    
        'White',                    
        '555-7890',                
        3000.00,                   
        'Ассистент',               
        3                           -- ManagerId (ID Bob)
    );
END;

BEGIN
    ShowSubordinates(1); 
END;

--4
CREATE OR REPLACE PROCEDURE MoveSubordinateBranch(
    p_OriginalManagerId IN NUMBER,  
    p_NewManagerId IN NUMBER          
) IS
BEGIN

    UPDATE Employees2
    SET ManagerId = p_NewManagerId
    WHERE ManagerId = p_OriginalManagerId;

    COMMIT; 
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLERRM);
END;

BEGIN
    MoveSubordinateBranch(
        3,  -- ID оригинального управляющего (например, John)
        2   -- ID нового управляющего (например, Alice)
    );
END;