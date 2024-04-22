; Библиотека функций для массивов

(defmacro with-struct (struct ar ofs &rest body)
  "Выполнить вычисление body и установить значения переменных структуры struct из массива arr по смещению ofs"
  `(let ,(struct-fields (eval struct) (eval ar) (eval ofs)) ,@body))

(defun struct-fields (struct arr ofs)
  "Преобразовывает структуру в список для let"
					;  (let ((attr (arr-get-num arr ofs num))
					;       ((type .. ))
   (car (foldl '(lambda (acc elem)
	    (let ((list (car acc))
		  (ofs (cdr acc))
		  (field (car elem))
		  (size (cdr elem)))
	      (cons (append list (list
				  (if (eq field 'str)
				      `(,(cadr elem) (arr-get-str ,arr ,ofs ,(cddr elem)))
				      `(,field (arr-get-num ,arr ,ofs ,size)))))
		    (if (eq field 'str) (+ ofs (cdr size)) (+ ofs size)))))
	  (cons nil ofs) struct)))

(defun arr-get-num (arr ofs size)
  "Прочесть из массива arr по смещению ofs size байт"
  (if (equal size 0) 0
    (let ((it (- size 1)))
      (+ (<< (aref arr (+ ofs it)) (<< it 3)) (arr-get-num arr ofs it)))))

(defun arr-set-num (arr ofs val size)
  "Записать в массив arr по смещению ofs значение val занимающее size байт"
    (for i 0 size
	 (seta arr (+ ofs i) (& val 0xff))
	 (setq val (>> val 8))))

(defun arr-get-str (arr ofs size)
  "Прочесть из массива arr по смещению ofs строку размером size"
  (if (equal size 0) ""
      (let ((s ""))
	(for i ofs (+ ofs size)
	     (setf s (concat s (code-char (aref arr i)))))
	s)))

;(defun write-struct (arr offs struct values)
  "Записать в массив arr по смещению ofs значения из хеш объекта values,"
  "используя структуру struct"
 ; (foldl '(lambda (a elem)
;	   (let ((name (car elem))
;		 (size (cdr elem)))
;	     )) offs struct))

; тесты
(defun with-struct-test ()
  (let ((s '((str name . 10) ; строковое поле из 10 байт
	     (f2 . 4)))
	(arr #(0 0 0x30 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38 0x39 1 0 0 0)))
    (with-struct s arr 2
      `(,name ,f2))))

(defun write-struct-test ()
  (let ((s '((str name . 10) ; строковое поле из 10 байт
	     (f2 . 4)))
	(arr #(0 0 0x30 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38 0x39 1 0 0 0)))
    (arr-set-num arr 1 0x1 4)
    arr))

(write-struct-test)
