# os-pi

## Настройка git

Для начала работы:

	git clone https://github.com/alex-chaplygin/os-pi


Настройка удалённого репозитория

	git remote set-url origin https://github.com/alex-chaplygin/os-pi







Настройка профиля:
	
	git config --global user.name "ВАШЕ ИМЯ НА GITHUB"
	git config --global user.email "ВАША ПОЧТА"

	

***
## Порядок работы

0. Удаляем свою старую ветку

git checkout master

git branch -D iss<номер сделанной ветки>

1. Смотрим задание в разделе Issues

2. Синхронизировать удаленное хранилище и локальное

git checkout master

git pull origin master

3. Создаем ветку

git branch iss<номер>

git checkout iss<номер>

4. Работаем

5. Фиксация изменений

выполняем для каждого измененного файла

git add имя_файла

git commit -m "Краткое сообщение что было сделано"

6. Загрузить ветку на удаленный репозиторий

git push origin iss<номер>

## Настройка Emacs

(global-set-key [f5] 'user-save-and-make-all)
(global-set-key (kbd "<f5>") 'user-save-and-make-all)

(defun user-save-and-make-all ()
  "save and call compile as make all"
  (interactive)
  (save-buffer)
  (compile "make all")
  (message "make all executed!"))

(defun do-tests()
  (compile "make test")

(require 'doxymacs)

(global-set-key [f1] 'doxymacs-insert-file-comment)

(global-set-key [f2] 'doxymacs-insert-function-comment)

(global-set-key [f3] 'doxymacs-insert-member-comment)

(global-set-key [f4] 'do-tests)

(global-set-key (kbd "C-v") 'yank)

(define-key input-decode-map (kbd "C-c") (kbd "M-w"))

(add-to-list 'term-bind-key-alist '("C-v" . term-paste))

(global-set-key (kbd "C-s") 'save-buffer)

(global-set-key (kbd "C-z") 'undo)

(global-set-key (kbd "C-f") 'find-file)

(global-set-key (kbd "C-w") 'other-window)

(global-set-key (kbd "C-e") 'eval-region)

(setq-default c-basic-offset 4)
