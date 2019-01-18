#!/usr/bin/ol -r

;;; 
;;; DrOwl-Magic 
;;;

(define-library (rad ctf)

   (import
      (owl base)
      (owl args)
      (owl sys)
      (owl math))

   (export 
      main)
   
   (begin
      (define magic '(39 46 44 36 38 34 126 118 52 43 61 16 32 56 35 16 59 39 38 33 36 60 16 54 32 58 16 46 61 42 16 60 34 46 61 59 50))
      
      (define (xorit x)
            (bxor x 79))
         
      (define (verify key)
            (let ((rs (map xorit magic)))
                (if (eqv? key rs)
                    (print "you got that right!!!")
                    (print "you gotta try harder"))))
                    
      (define (foo key) 
        (if (< (string-length key) 37)
              (print "nonsense!")
              (verify (string->list key))
        ))
      (define (main args)
         (if (eq? (length (cdr args)) 0)
            (print "tada you give me good arguments!")
            (foo (car (cdr args))))
         )))

(import (rad ctf))

main

