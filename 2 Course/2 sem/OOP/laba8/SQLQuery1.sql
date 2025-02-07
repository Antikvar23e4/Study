INSERT INTO [dbo].[Authors] ([author_id], [full_name], [country])
VALUES (1, N'Имя Автора', N'Страна');

INSERT INTO [dbo].[Book_Authors] ([book_id], [author_id])
VALUES (1, 1); 
INSERT INTO [dbo].[Books] ([book_id], [title], [format], [file_size], [UDC], [page_count], [publisher], [year_published], [upload_date], [image_path])
VALUES (1, N'Название книги', N'Формат', 1024, N'123.45', 300, N'Издательство', 2024, '2024-04-24', N'/путь/к/изображению.jpg');
select * from [dbo].[Books] 

