					; Глобальные переменные
(defvar *screen-width* 80); ширина экрана
(defvar *screen-height* 25) ; высота экрана 
					; Символы
(defvar +ul-char+ "\xc9") ; левый верхний двойной угол
(defvar +ur-char+ "\xbb") ; правый верхний двойной угол
(defvar +bl-char+ "\xc8") ; левый нижний двойной угол
(defvar +br-char+ "\xbc") ; правый нижний двойной угол
(defvar +h-char+ "\xcd") ; горизонтальная двойная черта
(defvar +v-char+ "\xba") ; вертикальная двойная черта
; Цвета
(defvar +black+ 0)
(defvar +blue+ 1)
(defvar +green+ 2)
(defvar +cyan+ 3)
(defvar +red+ 4)
(defvar +magenta+ 5)
(defvar +brown+ 6)
(defvar +light-gray+ 7)
(defvar +dark-gray+ 8)
(defvar +light-blue+ 9)
(defvar +light-green+ 10)
(defvar +light-cyan+ 11)
(defvar +light-red+ 12)
(defvar +light-magenta+ 13)
(defvar +yellow+ 14)
(defvar +white+ 15)


(defun fill-row (count char)
  "Печатает строку символов char длиной count"
  (for ii 0 count
      (putchar char)))

(defun fill-column (x y count char)
  "Печатает вертикальную линию из символов char длиной count, начиная с позиции x,y"
  (if (equal count 0) nil
    (progn
      (set-cursor x y)
      (putchar char)
      (fill-column x (+ y 1) (- count 1) char)))) 
  

(defun fill-rect (x y w h char)
    "Заполняет область символом char"
    "x,y - координаты левого верхнего угла"
    "w - ширина области, h - высота области"
    (let ((ww (if (> (+ x w) *screen-width*)
		  (- *screen-width* x) w))
	  (hh (if (> (+ y h) *screen-height*)
		  (- *screen-height* y) h)))
      (for i y (+ y hh)
	 (set-cursor x i)
	 (fill-row ww char))))

(defun print-rect (x y w h)
  "Отрисовывет рамку окна"
  "x,y - координаты левого верхнего угла"
  "w - ширина рамки, h - высота рамки"
  (set-cursor x y)
  (putchar +ul-char+)
  (fill-row (- w 2) +h-char+)
  (putchar +ur-char+)
  (fill-column x (+ y 1) (- h 2) +v-char+)
  (fill-column (+ x (- w 1)) (+ y 1) (- h 2) +v-char+)
  (set-cursor x (+ y (- h 1)))
  (putchar +bl-char+)
  (fill-row (- w 2) +h-char+)
  (putchar +br-char+))

(defclass element ()
  (x ; Координата x (относительно левого верхнего угла родительского элемента)
   y ; Координата y (относительно левого верхнего угла родительского элемента)
   width ; Ширина элемента
   height ; Высота элемента
   text ; Текст элемента
   color ; Цвет текста элемента
   back-color ; Цвет фона элемента
   active-color ; Цвет фона, когда элемент активен
   parent ; Родительский элемент
   children ; Список дочерних элементов
   max-children-bottom ; Максимальное расстояние от верхней границы родительского элемента до нижней границы дочерних элементов
   current-element-pos)) ; Позиция для добавления нового дочернего элемента, например (22 . 5)

(defmacro gen/calc-coord (name coord)
  `(defun ,name (elem)
     "Вычисление абсолютной координаты coord элемента elem"
     (if (null elem) 0
       (+ (slot elem ',coord) (,name (slot elem 'parent))))))

(gen/calc-coord calc-x x)
(gen/calc-coord calc-y y)

(defmethod draw-offset ((self element) offs-x offs-y)
  "Отрисовка элемента со смещением offs-x offs-y"
  (set-color (slot self 'color))
  (set-back-color (slot self 'back-color))
  (let ((new-x (+ (slot self 'x) offs-x))
	(new-y (+ (slot self 'y) offs-y))
	(w (slot self 'width))
	(h (slot self 'height)))
    (fill-rect new-x new-y w h " ")
    (app '(lambda (el) (draw-offset el new-x new-y)) (slot self 'children))))

(defmethod draw ((self element))
  (draw-offset self 0 0))

(defmethod add-child ((self element) child)
  "Добавление дочернего элемента child"
  (setf (slot self 'children) (append (slot self 'children) (list child)))
  (setf (slot child 'parent) self)
  (let* ((cur-x (car (slot self 'current-element-pos)))
	 (cur-y (cdr (slot self 'current-element-pos)))
	 (cur-width (+ cur-x (slot child 'width))))
    ;(when (> cur-width (slot self 'width)) (setf (slot self 'width) cur-width))
    (update-width self cur-width)
    (setf (slot child 'x) cur-x)
    (setf (slot child 'y) cur-y)
    (setf (slot self 'current-element-pos) (cons cur-width cur-y))) 
  nil)

(defun update-width (elem width)
  "Изменяет ширину элемента elem на width, если width больше ширины элемента"
  "Повторяет это для родительского элемента"
  (unless (null elem)
    (let ((x (slot elem 'x))
	  (w (slot elem 'width)))
      (when (> width w) (setf (slot elem 'width) width))
      (update-width (slot elem 'parent) (+ width x)))))

(defmethod align ((self element) name-pos)
  "Выровнять элемент относительно родителя или экрана для окна"
  (let* ((parent (slot self 'parent))
	 (parent-x (slot parent 'x))
	 (parent-width (slot parent 'width))
	 (self-width (slot self 'width)))
    (setf (slot self 'x) 
	  (case name-pos
	    ('left parent-x)
	    ('right (- (+ parent-x parent-width) self-width))
	    ('center (- (+ parent-x (/ parent-width 2)) (/ self-width 2)))))))
