;; This is the official Emacs init file for the course IOOPM. It
;; uses English, not because anyone thinks it's cooler than
;; Swedish, but to avoid encoding problems with using Swedish
;; characters. Put it in `~/.emacs.d/init.el` to use it for your
;; own Emacs. You can use as many or as few of these settings as
;; you would like. Experiment and try to find a set-up that suits
;; you!
;;
;; Some settings in this file are commented out. They are the ones
;; that require some choice of parameter (such as a color) or that
;; might be considered more intrusive than other settings (such as
;; linum-mode).
;;
;; Whenever you come across something that looks like this
;;
;;    (global-set-key (kbd "C-e") 'move-end-of-line)
;;
;; it is a command that sets the keyboard shortcut for some
;; function. If you find a function that you like, whose keyboard
;; shortcut you don't like, you can (and should!) always change it to
;; something that you do like.
;;
;; This folder might be updated later in the course, so check back
;; later for more customizations!
;;


;; ===========
;; Appearance
;; ===========

;; Disable the menu bar (2013-08-20)
(menu-bar-mode -1)

;; Disable the tool bar (2013-08-20)
(tool-bar-mode -1)

;; Disable the scroll bar (2013-08-20)
(scroll-bar-mode -1)

;; Turn off annoying splash screen (2013-08-20)
(setq inhibit-splash-screen t)

;; Set which colors to use (2013-08-20)
;; You can see a list of all the available colors by checking the
;; variable "color-name-rgb-alist" (Type "C-h v color-name-rgb-alist
;; <RET>"). Most normal color names work, like black, white, red,
;; green, blue, etc.
; (set-background-color "black")
; (set-foreground-color "white")
; (set-cursor-color "white")

;; Set a custom color theme (2013-08-20)
;; NB! Needs Emacs 24.X!
;; You can also try using a custom theme, which changes more colors
;; than just the three above. For a list of all available themes,
;; press "M-x customize-themes <RET>". You can also use a theme in
;; combination with the above set-color-commands.
; (load-theme 'wombat)


;; ===========
;; Navigation
;; ===========

;; Show both line and column number in the bottom of the buffer (2013-08-20)
(column-number-mode t)

;; Show parenthesis matching the one below the cursor (2013-08-20)
(show-paren-mode t)

;; Show line numbers to the left of all buffers (2014-09-09)
; (global-linum-mode t)

;; Sentences are not followed by two spaces (2014-08-26)
;; Makes navigating with M-e and M-a (forward/backward senctence)
;; behave like you would expect
(setq sentence-end-double-space nil)

;; C-SPC after C-u C-SPC cycles mark stack (2013-08-20)
(setq-default set-mark-command-repeat-pop t)

;; Save-place (2013-08-20)
;; Remember the cursor position when you close a file, so that you
;; start with the cursor in the same position when opening it again
(setq save-place-file "~/.emacs.d/saveplace")
(setq-default save-place t)
(require 'saveplace)

;; Recent files (2013-08-20)
;; Enable a command to list your most recently edited files. If you
;; know you are opening a file that you have edited recently, this
;; should be faster than using find-file ("C-x C-f"). The code below
;; binds this to the keyboard shortcut "C-x C-r", which replaces the
;; shortcut for the command find-file-read-only.
(require 'recentf)
(recentf-mode 1)
(setq recentf-max-menu-items 25)
(global-set-key (kbd "C-x C-r") 'recentf-open-files)


;; ===========
;; Editing
;; ===========

;; Allow deletion of selected text with <DEL> (2013-08-20)
(delete-selection-mode 1)

;; Use multiple spaces instead of tab characters (2013-08-20)
(setq-default indent-tabs-mode nil)

;; hippie-expand instead of dabbrev-expand (2013-08-20)
;; dabbrev-expand will try to expand the word under the cursor by
;; searching your open buffers for words beginning with the same
;; characters. For example, if you have written "printf" in an open
;; buffer you can just write "pr" and expand it to the full
;; word. hippie-expand does the same kind of search, plus some
;; additional searching, such as in your kill ring or the names of the
;; files you have open.
(global-set-key (kbd "M-/") 'hippie-expand)