CREATE TABLE Employees4 (
    EmployeeId INT PRIMARY KEY,
    Name NVARCHAR(255) NOT NULL,
    SecondName NVARCHAR(255),
    PhoneNumber NVARCHAR(20),
    Salary DECIMAL(10, 2),
    Job NVARCHAR(100),
	PositionHierarchy HIERARCHYID
);

CREATE  SEQUENCE Seq_EmployeeID START WITH 1;

CREATE PROCEDURE AddEmployee (
    @Name NVARCHAR(255), 
	@SecondName NVARCHAR(255),
    @PhoneNumber NVARCHAR(20),
    @Salary DECIMAL(10, 2),
    @Job NVARCHAR(100),
    @ParentID INT -- Родительский узел
)
AS
BEGIN
    DECLARE @EmployeeID INT = NEXT VALUE FOR Seq_EmployeeID;
    DECLARE @PositionHierarchy HIERARCHYID;
    DECLARE @LastChild HIERARCHYID;
  DECLARE @ParentHierarchy HIERARCHYID;

    IF @ParentID = 0
    BEGIN
      SET @PositionHierarchy = HIERARCHYID::GetRoot();
    END
    ELSE
    BEGIN
      SELECT @ParentHierarchy = PositionHierarchy FROM Employees4 WHERE EmployeeID = @ParentID;

      SELECT @LastChild = MAX(PositionHierarchy) FROM Employees4 WHERE PositionHierarchy.GetAncestor(1) = @ParentHierarchy;

      SET @PositionHierarchy = @ParentHierarchy.GetDescendant(@LastChild, NULL);
    END

    INSERT INTO Employees4 (EmployeeID, Name, SecondName, PhoneNumber, Salary, Job, PositionHierarchy) 
    VALUES (@EmployeeID, @Name, @SecondName, @PhoneNumber, @Salary,@Job, @PositionHierarchy);
END;

-- Добавление сотрудников с указанием родительского узла
EXEC AddEmployee 'Sophia', 'Miller', '123-456-7899', 60000.00, 'Директор', 0; 
EXEC AddEmployee 'Sophia', 'Miller', '123-456-7899', 60000.00, 'Менеджер', 1; 
EXEC AddEmployee 'Daniel', 'Johnson', '123-456-7800', 50000.00, 'Специалист', 1; 
EXEC AddEmployee 'Mia', 'Wilson', '123-456-7801', 55000.00, 'Ассистент', 2;
EXEC AddEmployee 'Mia', 'Wilson', '123-456-7801', 55000.00, 'Ассистент', 2;

ALTER PROCEDURE GetEmployeeHierarchy
    @EmployeeID INT
AS
BEGIN
    DECLARE @HierarchyID HIERARCHYID;

    SELECT @HierarchyID = PositionHierarchy FROM Employees4 WHERE EmployeeID = @EmployeeID;
    SELECT 
        EmployeeID,
        Name,
        PositionHierarchy.ToString() AS HierarchyPath,
        PositionHierarchy.GetLevel() AS HierarchyLevel
    FROM Employees4 WHERE Employees4.PositionHierarchy.IsDescendantOf(@HierarchyID) = 1 ORDER BY EmployeeID;
END;


EXEC GetEmployeeHierarchy @EmployeeID = 1; 

create PROCEDURE MoveEmployeeBranch (
    @SourceEmployeeID INT,
    @TargetEmployeeID INT 
)
AS
BEGIN
    DECLARE @SourceHierarchy HIERARCHYID;
    DECLARE @TargetHierarchy HIERARCHYID;
    DECLARE @NewHierarchy HIERARCHYID;
    
    SELECT @SourceHierarchy = PositionHierarchy FROM Employees4 WHERE EmployeeID = @SourceEmployeeID;

    SELECT @TargetHierarchy = PositionHierarchy FROM Employees4 WHERE EmployeeID = @TargetEmployeeID;

    IF @TargetHierarchy.IsDescendantOf(@SourceHierarchy) = 1
    BEGIN
      RAISERROR('Невозможно переместить узел в его потомка', 16, 1);
      RETURN;
    END

    DECLARE @LastChild HIERARCHYID;
    SELECT @LastChild = MAX(PositionHierarchy) FROM Employees4 WHERE PositionHierarchy.GetAncestor(1) = @TargetHierarchy;

    SET @NewHierarchy = @TargetHierarchy.GetDescendant(@LastChild, NULL);

    WITH CTE_Employees AS (
        SELECT EmployeeID, PositionHierarchy FROM Employees4 WHERE PositionHierarchy.IsDescendantOf(@SourceHierarchy) = 1
    )

    UPDATE EP SET EP.PositionHierarchy = CTE.PositionHierarchy.GetReparentedValue(@SourceHierarchy, @NewHierarchy) 
    FROM Employees4 EP JOIN CTE_Employees CTE ON EP.EmployeeID = CTE.EmployeeID;
END;


EXEC MoveEmployeeBranch @SourceEmployeeID = 2, @TargetEmployeeID = 3;

EXEC GetEmployeeHierarchy @EmployeeID = 1;

EXEC AddEmployee 'GEGDG', 'Wilson', '123-456-7801', 55000.00, 'Ассистент', 1;
EXEC AddEmployee 'GEGSDFSFDG', 'Wilson', '123-456-7801', 55000.00, 'Ассистент', 8;

EXEC MoveEmployeeBranch @SourceEmployeeID = 7, @TargetEmployeeID = 3;