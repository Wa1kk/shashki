(defvar *bin-read-src*) ; массив для чтения двоичных данных
(defvar *bin-read-ptr*) ; индекс текущего элемента для чтения
(defvar *endianness* 'big) ; порядок байт
(defvar *bit-num*) ;счетчик бит в текущем байте
(defvar *cur-byte*) ;текущий байт для чтения бит

(defun set-bin-src (arr)
  "Устанавливает источник для чтения байт"
  "param: arr - источник"
  (setq *bin-read-src* arr)
  (setq *bin-read-ptr* -1)
  (setq *bit-num* 0))

(defun set-big-endian ()
  "Устанавливает порядок байт на старший впереди"
  (setq *endianness* 'big))

(defun set-little-endian ()
  "Устанавливает порядок байт на младший впереди"
  (setq *endianness* 'little))

(defun get-byte ()
  "Возвращает очередной байт в виде числа"
  (aref *bin-read-src* (setq *bin-read-ptr* (++ *bin-read-ptr*))))

(defun get-word ()
  "Возвращает очередные два байта в виде числа"
  (if (eq *endianness* 'big)
      (+ (<< (get-byte) 8) (get-byte))
    (+ (get-byte) (<< (get-byte) 8))))

(defun get-4bit ()
  "Возвращает пару из двух значений по 4 бита"
  (let ((b (get-byte)))
    (cons (>> b 4) (& b 0xf))))

(defun get-bit ()
  "Читает один бит из источника"
  (when (= *bit-num* 0)
    (setq *cur-byte* (get-byte))
    (setq *bit-num* (if (eq *endianness* 'big) 8 -1)))
  (& 1 (>> *cur-byte* (setq *bit-num* (if (eq *endianness* 'big) (-- *bit-num*) (++ *bit-num*))))))
