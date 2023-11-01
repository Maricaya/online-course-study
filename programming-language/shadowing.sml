val a = 10;
(*
 a : int
 a -> 10
*)

val b = a *2;
(*
 b -> 20
*)

val a = 5;
(*
 a -> 5,b -> 20
*)

val c = b;


(* functions.sml  *)

val x = 7;
(*y>0*)
fun pow(x: int, y: int) =
    if y=0
    then 1
    else x * pow(x,y-1);

fun cube(x: int) =
    pow(x, 3);

val sixtyfour = cube(4);

val fortytwo = pow(2, 2+2) + pow(4,2) + cube(2) + 2;


(* pairs and tuples.sml  *)
fun swap (pr: int*bool) =
    (#2 pr, #1 pr);

swap(7, true);

(* (int*int) * (int*int) -> int  *)
fun sum_two_pairs (pr1: int*int, pr2: int*int) =
    (#1 pr1) + (#2 pr1) + (#1 pr2) + (#2 pr2);

(* int*int -> int*int *)  
fun div_mod (x: int, y: int) =
    (x div y, x mod y);

fun sort_pair (pr: int*int) =
    if (#1 pr) < (#2 pr)
    then pr
    else (#2 pr, #1 pr);

sort_pair(3, 4);


(*lists.sml  *)
val x = [7,8];
5::x;
null [];
hd x;
tl x;

(* listsFunctions.sml  *)	
fun sum_list (xs : int list) =
    if null xs
    then 0
    else hd xs + sum_list(tl xs);

fun list_product (xs: int list) =
    if null xs
    then 1
    else hd xs * list_product(tl xs);

fun countdown (x: int) =
    if x=0
    then []
    else x :: countdown(x-1);

fun factorial (n:int) =
    list_product(countdown(n));

fun append (xs: int list, ys: int list) =
    if null xs
    then ys
    else (hd xs) :: append (tl xs, ys);

fun sum_pair_list (xs: (int*int) list) =
    if null xs
    then 0
    else #1 (hd xs) + #2 (hd xs) + sum_pair_list(tl xs);

sum_pair_list([(3,4), (5,6)]);

fun firsts(xs: (int*int) list) =
    if null xs
    then []
    else (#1 (hd xs)) :: firsts(tl xs);
			     
fun seconds(xs: (int*int) list) =
    if null xs
    then []
    else (#2 (hd xs)) :: seconds(tl xs);

fun sum_pair_list2 (xs: (int*int) list) =
    (sum_list(firsts xs)) + (sum_list (seconds xs));
		       
fun silly1 (z: int) =
    let
	val x = if z > 0 then z else 34
	val y = x + z + 9
    in
	if x > y then x * 2 else y * y
    end;

fun silly2 () =
    let
	val x = 1
    in
	(let val x = 2 in x+1 end) + (let val y=x+2 in y+1 end)
    end;

(* [3,4,5,6] *)


