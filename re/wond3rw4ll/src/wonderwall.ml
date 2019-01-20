let flag = [119; 51; 76; 99; 48; 109; 51; 95; 116; 48; 95; 116; 72; 51; 95; 56; 76; 52; 99; 75; 95; 112; 52; 82; 52; 68; 51];;

let duration = [100; 200; 300; 1000; 10000; 100000; 1000000; 10000000; 10000000; 100000000; 100000000; 1000000000; 10000000000; 100000000000; 100000000000; 100000000000; 1000000000000; 1000000000000; 1000000000000; 1000000000000; 1000000000000; 1000000000000; 1000000000000; 1000000000000; 1000000000000; 1000000000000; 100000000000000];;

let n = List.length flag;;

let delay idx =
    Unix.sleep (List.nth duration idx)
;;

let print_flag idx = 
    Printf.printf "%c" (char_of_int (List.nth flag idx));
    flush stdout
;;

let time f x =
    let t = Unix.gettimeofday () in
    let _ = f x in
    let diff = Unix.gettimeofday() -. t in
    diff
;;

let in_time x idx =
    let a = float_of_int (List.nth duration idx)
    and x = abs_float x in
    let diff = abs_float (a -. x) in
    if diff <= 1.0 then true else false
;;

let validate idx =
    let t = time delay idx in
    let pass = in_time t idx in
    if pass = false then
        exit 1
    else
        print_flag idx
;;

let (--) i j =
    let rec aux n acc =
        if n < i then
            acc
        else
            aux (n-1) (n :: acc)
    in aux j []
;;

List.map validate (0--(n-1));;
