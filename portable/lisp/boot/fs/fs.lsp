(defvar *file-system*) ; глобальный объект файловой системы
; класс абстрактной файловой системы
(defclass FileSystem () ())
; класс абстрактного файла
(defclass File ()
  (name ;    имя
   size ;    размер файла	   
   position ; позиция чтения/записи
   blocks ;   список номеров блоков, например (14 15 16)
   dir)) ;      для каталогов - дерево
