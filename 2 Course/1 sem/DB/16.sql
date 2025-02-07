USE UNIVER;
/*1 ����������� �������� �������� XML-��������� � ������ PATH �� ������� TEACHER ��� �������������� ������� ����. */
SELECT PULPIT.FACULTY[���������], TEACHER.PULPIT[�������], TEACHER.TEACHER_NAME[�������������]
FROM TEACHER INNER JOIN PULPIT ON TEACHER.PULPIT = PULPIT.PULPIT
WHERE TEACHER.PULPIT = '����' FOR XML RAW, ROOT('�������������_����'),ELEMENTS;

/*2 ����������� �������� �������� XML-��������� � ������ AUTO �� ������ SELECT-������� � �������� AUDITORIUM � AUDI-TORIUM_TYPE, ������� �������� ������-��� �������:
������������ ���������, ������������ ���� ��������� � �����������. ����� ������ ���������� ���������. */
SELECT AUDITORIUM.AUDITORIUM [���������], AUDITORIUM.AUDITORIUM_TYPE [���],AUDITORIUM.AUDITORIUM_CAPACITY [�����������] 
FROM AUDITORIUM JOIN AUDITORIUM_TYPE ON AUDITORIUM.AUDITORIUM_TYPE = AUDITORIUM_TYPE.AUDITORIUM_TYPE
WHERE AUDITORIUM.AUDITORIUM_TYPE = '��' FOR XML AUTO, ROOT('������'),ELEMENTS ;

/*3 ����������� XML-��������, ���������� ������ � ���� ����� ������� �����������, ������� ������� �������� � ������� SUBJECT. 
����������� ��������, ����������� ������ � ����������� �� XML-��������� � �������-���� �� � ������� SUBJECT. 
��� ���� ��������� ��������� ������� OPENXML � ����������� INSERT� SE-LECT. */
DECLARE @H INT = 0,
@SBJ VARCHAR(3000) = '<?xml version="1.0" encoding="windows-1251" ?>
                      <����������>
					     <���������� ���="����1" ��������="������ �������1" �������="����" />
						 <���������� ���="����2" ��������="������ �������2" �������="����" />
						 <���������� ���="����3" ��������="������ �������3" �������="����" />
					  </����������>';
EXEC SP_XML_PREPAREDOCUMENT @H OUTPUT, @SBJ;
INSERT SUBJECT SELECT[���], [��������], [�������] FROM OPENXML(@H, '/����������/����������',0)
    WITH([���] CHAR(10), [��������] VARCHAR(100), [�������] CHAR(20))		;

SELECT * FROM SUBJECT WHERE PULPIT = '����'

EXEC SP_XML_REMOVEDOCUMENT @H;        

/*4 ��������� ������� STUDENT ����������� XML-���������, ���������� ���������� ������ ��������: ����� � ����� ��������, ������ �����, ���� ������ � ����� ��������. 
����������� ��������, � ������� ������� �������� INSERT, ����������� ������ � XML-��������.
�������� � ���� �� �������� �������� UP-DATE, ���������� ������� INFO � ����� ������ ������� STUDENT � �������� SE-LECT, ����������� �������������� ����p.
� SELECT-������� ������������ ������ QUERY � VALUEXML-����. */
INSERT INTO STUDENT(IDGROUP, NAME, BDAY, INFO)
VALUES(4, '�������� �.�.', '2005-04-28',
	'<�������>
		<������� �����="��" �����="1234567" ����="20-12-2012" />
		<�������>+375292692233</�������>
		<�����>
			<������>��������</������>
			<�����>�����</�����>
			<�����>����������</�����>
			<���>11</���>
			<��������>132</��������>
		</�����>
	</�������>');
GO
SELECT * FROM STUDENT WHERE NAME = '�������� �.�.'
GO
UPDATE STUDENT SET INFO = 
	'<�������>
		<������� �����="��" �����="1234567" ����="20-12-2012" />
		<�������>+375292692233</�������>
		<�����>
			<������>��������</������>
			<�����>�����</�����>
			<�����>���������</�����>
			<���>11</���>
			<��������>132</��������>
		</�����>
	</�������>' WHERE NAME = '�������� �.�.'
GO
SELECT NAME[���], INFO.value('(�������/�������/@�����)[1]', 'CHAR(2)')[����� ��������],
	INFO.value('(�������/�������/@�����)[1]', 'VARCHAR(20)')[����� ��������],
	INFO.query('/�������/�����')[�����]
		FROM  STUDENT
			WHERE NAME = '�������� �.�.';  

DELETE FROM STUDENT 	WHERE NAME = '�������� �.�.';  

/*5 �������� (ALTER TABLE) ������� STUDENT � ���� ������ UNIVER ����� �������, ����� �������� ��������������� ������� � ������ INFO ���������������� ���������� XML-���� (XML SCHEMACOLLECTION), �����������-��� � ������ �����. 
����������� ��������, ��������������� ���� � ������������� ������ (��������� IN-SERT � UPDATE) � ������� INFO ������� STUDENT, ��� ���������� ������, ��� � ����������.
����������� ������ XML-����� � �������� �� � ��������� XML-���� � �� UNIVER.*/
create xml schema collection Student as
N'<?xml version="1.0" encoding="utf-16" ?>
<xs:schema attributeFormDefault="unqualified"
   elementFormDefault="qualified"
   xmlns:xs="http://www.w3.org/2001/XMLSchema">
<xs:element name="�������">
<xs:complexType><xs:sequence>
<xs:element name="�������" maxOccurs="1" minOccurs="1">
  <xs:complexType>
    <xs:attribute name="�����" type="xs:string" use="required" />
    <xs:attribute name="�����" type="xs:unsignedLong" use="required"/>
    <xs:attribute name="����"  use="required">
  <xs:simpleType>  <xs:restriction base ="xs:string">
    <xs:pattern value="[0-9]{2}.[0-9]{2}.[0-9]{4}"/>
   </xs:restriction>   </xs:simpleType>
     </xs:attribute>
  </xs:complexType>
</xs:element>
<xs:element maxOccurs="3" name="�������" type="xs:unsignedLong"/>
<xs:element name="�����">   <xs:complexType><xs:sequence>
   <xs:element name="������" type="xs:string" />
   <xs:element name="�����" type="xs:string" />
   <xs:element name="�����" type="xs:string" />
   <xs:element name="���" type="xs:string" />
   <xs:element name="��������" type="xs:string" />
</xs:sequence></xs:complexType>  </xs:element>
</xs:sequence></xs:complexType>
</xs:element></xs:schema>';

create table STUDENT2 
(     
      IDGROUP integer  foreign key  references GROUPS(IDGROUP),        
      NAME nvarchar(100), 
      BDAY  date,
      INFO   xml(STUDENT), 
  );

INSERT INTO STUDENT2(IDGROUP, NAME, BDAY, INFO)
VALUES(4, '������ �.�.', '2004-11-14',
  '<�������>
    <������� �����="��" �����="4112033" ����="09.09.2009" />
    <�������>+375294949293</�������>
    <�����>
      <������>��������</������>
      <�����>������</�����>
      <�����>�������</�����>
      <���>23</���>
      <��������>12</��������>
    </�����>
  </�������>');

INSERT INTO STUDENT2(IDGROUP, NAME, BDAY, INFO)
VALUES(4, '��������� �.�.', '2004-11-14',
  '<�������>
    <������� �����="��" �����="4112033" ����="11.11.11" />
    <�������>+375294949293</�������>
    <�����>
      <������>��������</������>
      <�����>������</�����>
      <�����>�������</�����>
      <���>23</���>
      <��������>16</��������>
    </�����>
  </�������>');

SELECT * FROM STUDENT2
DROP TABLE STUDENT2;


create xml schema collection PhoneNumberSchema AS
N'<?xml version="1.0" encoding="utf-16" ?>
<xs:schema attributeFormDefault="unqualified"
   elementFormDefault="qualified"
   xmlns:xs="http://www.w3.org/2001/XMLSchema">
   <xs:element name="�����_��������">
      <xs:complexType>
         <xs:sequence>
            <xs:element name="�����" type="xs:string" />
            <xs:element name="��������" type="xs:string" />
            <xs:element name="������" type="xs:string" />
         </xs:sequence>
      </xs:complexType>
   </xs:element>
</xs:schema>';

create table STUDENT3
(     
      IDGROUP integer  foreign key  references GROUPS(IDGROUP),        
      NAME nvarchar(100), 
      BDAY  date,
      PHONE   xml(PhoneNumberSchema),  
  );

INSERT INTO STUDENT3(IDGROUP, NAME, BDAY, PHONE)
VALUES(4, '������ �.�.', '2004-11-14',
  '<�����_��������>
        <�����>+1234567890</�����>
        <��������>���</��������>
        <������>iPhone</������>
    </�����_��������>');

SELECT * FROM STUDENT3
DELETE FROM STUDENT3 WHERE NAME = '������ �.�.'