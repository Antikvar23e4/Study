USE UNIVER;
/*1 Разработать сценарий создания XML-документа в режиме PATH из таблицы TEACHER для преподавателей кафедры ИСиТ. */
SELECT PULPIT.FACULTY[ФАКУЛЬТЕТ], TEACHER.PULPIT[КАФЕДРА], TEACHER.TEACHER_NAME[ПРЕПОДАВАТЕЛЬ]
FROM TEACHER INNER JOIN PULPIT ON TEACHER.PULPIT = PULPIT.PULPIT
WHERE TEACHER.PULPIT = 'ИСИТ' FOR XML RAW, ROOT('ПРЕПОДАВАТЕЛИ_ИСИТ'),ELEMENTS;

/*2 Разработать сценарий создания XML-документа в режиме AUTO на основе SELECT-запроса к таблицам AUDITORIUM и AUDI-TORIUM_TYPE, который содержит следую-щие столбцы:
наименование аудитории, наименование типа аудитории и вместимость. Найти только лекционные аудитории. */
SELECT AUDITORIUM.AUDITORIUM [АУДИТОРИЯ], AUDITORIUM.AUDITORIUM_TYPE [ТИП],AUDITORIUM.AUDITORIUM_CAPACITY [ВМЕСТИМОСТЬ] 
FROM AUDITORIUM JOIN AUDITORIUM_TYPE ON AUDITORIUM.AUDITORIUM_TYPE = AUDITORIUM_TYPE.AUDITORIUM_TYPE
WHERE AUDITORIUM.AUDITORIUM_TYPE = 'ЛК' FOR XML AUTO, ROOT('СПИСОК'),ELEMENTS ;

/*3 Разработать XML-документ, содержащий данные о трех новых учебных дисциплинах, которые следует добавить в таблицу SUBJECT. 
Разработать сценарий, извлекающий данные о дисциплинах из XML-документа и добавля-ющий их в таблицу SUBJECT. 
При этом применить системную функцию OPENXML и конструкцию INSERT… SE-LECT. */
DECLARE @H INT = 0,
@SBJ VARCHAR(3000) = '<?xml version="1.0" encoding="windows-1251" ?>
                      <ДИСЦИПЛИНЫ>
					     <ДИСЦИПЛИНА КОД="ПРЕД1" НАЗВАНИЕ="Крутой предмет1" КАФЕДРА="ИСИТ" />
						 <ДИСЦИПЛИНА КОД="ПРЕД2" НАЗВАНИЕ="Крутой предмет2" КАФЕДРА="ИСИТ" />
						 <ДИСЦИПЛИНА КОД="ПРЕД3" НАЗВАНИЕ="Крутой предмет3" КАФЕДРА="ИСИТ" />
					  </ДИСЦИПЛИНЫ>';
EXEC SP_XML_PREPAREDOCUMENT @H OUTPUT, @SBJ;
INSERT SUBJECT SELECT[КОД], [НАЗВАНИЕ], [КАФЕДРА] FROM OPENXML(@H, '/ДИСЦИПЛИНЫ/ДИСЦИПЛИНА',0)
    WITH([КОД] CHAR(10), [НАЗВАНИЕ] VARCHAR(100), [КАФЕДРА] CHAR(20))		;

SELECT * FROM SUBJECT WHERE PULPIT = 'ИСИТ'

EXEC SP_XML_REMOVEDOCUMENT @H;        

/*4 Используя таблицу STUDENT разработать XML-структуру, содержащую паспортные данные студента: серию и номер паспорта, личный номер, дата выдачи и адрес прописки. 
Разработать сценарий, в который включен оператор INSERT, добавляющий строку с XML-столбцом.
Включить в этот же сценарий оператор UP-DATE, изменяющий столбец INFO у одной строки таблицы STUDENT и оператор SE-LECT, формирующий результирующий набоp.
В SELECT-запросе использовать методы QUERY и VALUEXML-типа. */
INSERT INTO STUDENT(IDGROUP, NAME, BDAY, INFO)
VALUES(4, 'Немкович А.В.', '2005-04-28',
	'<СТУДЕНТ>
		<ПАСПОРТ СЕРИЯ="МР" НОМЕР="1234567" ДАТА="20-12-2012" />
		<ТЕЛЕФОН>+375292692233</ТЕЛЕФОН>
		<АДРЕС>
			<СТРАНА>Беларусь</СТРАНА>
			<ГОРОД>Минск</ГОРОД>
			<УЛИЦА>Кунцевщина</УЛИЦА>
			<ДОМ>11</ДОМ>
			<КВАРТИРА>132</КВАРТИРА>
		</АДРЕС>
	</СТУДЕНТ>');
GO
SELECT * FROM STUDENT WHERE NAME = 'Немкович А.В.'
GO
UPDATE STUDENT SET INFO = 
	'<СТУДЕНТ>
		<ПАСПОРТ СЕРИЯ="МР" НОМЕР="1234567" ДАТА="20-12-2012" />
		<ТЕЛЕФОН>+375292692233</ТЕЛЕФОН>
		<АДРЕС>
			<СТРАНА>Беларусь</СТРАНА>
			<ГОРОД>Минск</ГОРОД>
			<УЛИЦА>Советская</УЛИЦА>
			<ДОМ>11</ДОМ>
			<КВАРТИРА>132</КВАРТИРА>
		</АДРЕС>
	</СТУДЕНТ>' WHERE NAME = 'Немкович А.В.'
GO
SELECT NAME[ФИО], INFO.value('(СТУДЕНТ/ПАСПОРТ/@СЕРИЯ)[1]', 'CHAR(2)')[СЕРИЯ ПАСПОРТА],
	INFO.value('(СТУДЕНТ/ПАСПОРТ/@НОМЕР)[1]', 'VARCHAR(20)')[НОМЕР ПАСПОРТА],
	INFO.query('/СТУДЕНТ/АДРЕС')[АДРЕС]
		FROM  STUDENT
			WHERE NAME = 'Немкович А.В.';  

DELETE FROM STUDENT 	WHERE NAME = 'Немкович А.В.';  

/*5 Изменить (ALTER TABLE) таблицу STUDENT в базе данных UNIVER таким образом, чтобы значения типизированного столбца с именем INFO контролировались коллекцией XML-схем (XML SCHEMACOLLECTION), представлен-ной в правой части. 
Разработать сценарии, демонстрирующие ввод и корректировку данных (операторы IN-SERT и UPDATE) в столбец INFO таблицы STUDENT, как содержащие ошибки, так и правильные.
Разработать другую XML-схему и добавить ее в коллекцию XML-схем в БД UNIVER.*/
create xml schema collection Student as
N'<?xml version="1.0" encoding="utf-16" ?>
<xs:schema attributeFormDefault="unqualified"
   elementFormDefault="qualified"
   xmlns:xs="http://www.w3.org/2001/XMLSchema">
<xs:element name="студент">
<xs:complexType><xs:sequence>
<xs:element name="паспорт" maxOccurs="1" minOccurs="1">
  <xs:complexType>
    <xs:attribute name="серия" type="xs:string" use="required" />
    <xs:attribute name="номер" type="xs:unsignedLong" use="required"/>
    <xs:attribute name="дата"  use="required">
  <xs:simpleType>  <xs:restriction base ="xs:string">
    <xs:pattern value="[0-9]{2}.[0-9]{2}.[0-9]{4}"/>
   </xs:restriction>   </xs:simpleType>
     </xs:attribute>
  </xs:complexType>
</xs:element>
<xs:element maxOccurs="3" name="телефон" type="xs:unsignedLong"/>
<xs:element name="адрес">   <xs:complexType><xs:sequence>
   <xs:element name="страна" type="xs:string" />
   <xs:element name="город" type="xs:string" />
   <xs:element name="улица" type="xs:string" />
   <xs:element name="дом" type="xs:string" />
   <xs:element name="квартира" type="xs:string" />
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
VALUES(4, 'Пушкин А.С.', '2004-11-14',
  '<студент>
    <паспорт серия="МР" номер="4112033" дата="09.09.2009" />
    <телефон>+375294949293</телефон>
    <адрес>
      <страна>Беларусь</страна>
      <город>Кобрин</город>
      <улица>Дружная</улица>
      <дом>23</дом>
      <квартира>12</квартира>
    </адрес>
  </студент>');

INSERT INTO STUDENT2(IDGROUP, NAME, BDAY, INFO)
VALUES(4, 'Ломаносов М.В.', '2004-11-14',
  '<студент>
    <паспорт серия="МР" номер="4112033" дата="11.11.11" />
    <телефон>+375294949293</телефон>
    <адрес>
      <страна>Беларусь</страна>
      <город>Кобрин</город>
      <улица>Дружная</улица>
      <дом>23</дом>
      <квартира>16</квартира>
    </адрес>
  </студент>');

SELECT * FROM STUDENT2
DROP TABLE STUDENT2;


create xml schema collection PhoneNumberSchema AS
N'<?xml version="1.0" encoding="utf-16" ?>
<xs:schema attributeFormDefault="unqualified"
   elementFormDefault="qualified"
   xmlns:xs="http://www.w3.org/2001/XMLSchema">
   <xs:element name="номер_телефона">
      <xs:complexType>
         <xs:sequence>
            <xs:element name="номер" type="xs:string" />
            <xs:element name="оператор" type="xs:string" />
            <xs:element name="модель" type="xs:string" />
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
VALUES(4, 'Пушкин А.С.', '2004-11-14',
  '<номер_телефона>
        <номер>+1234567890</номер>
        <оператор>МТС</оператор>
        <модель>iPhone</модель>
    </номер_телефона>');

SELECT * FROM STUDENT3
DELETE FROM STUDENT3 WHERE NAME = 'Пушкин А.С.'