val x = {bar = (1+2, true andalso true) ,foo=3+4, baz = (false, 9)};
val my_niece = {name = "Amelia", id=41123-12};

val a_pair = (3+1, 4+2);

val id = #id my_niece;


datatype mytype = TwoInts of int*int | Str of string | Pizza;

fun f(x: mytype) =
    case x of
	Pizza => 3
      | Str s => 8
      | TwoInts(i1, i2) => i1+i2;


fun f Pizza;

datatype suit = Club | Diamond | Heart | Spade;

datatype exp = Constant of int | Negate of exp | Add of exp*exp | Multiply of exp*exp

(* Add(Constant(10+9), Negate(Constant 4))  *)

fun eval e =
    case e of
	Constant i => i
      | Negate e2 => ~ (eval e2)
      | Add(e1, e2) => (eval e1) + (eval e2)
      | Multipy(e1, e2) =>   (eval e1) * (eval e2);

fun max_constant e =
    let
	    fun max_of_two (e1, e2) =
	        Int.max(max_constant e1,max_constant e2)
    in
	    case e of
            Constant i => i
            | Negate e2 => max_constant(e2)
            | Add(e1,e2) => max_of_two(e1,e2)
            | Multipy(e1, e2) => max_of_two(e1,e2)
    end

fun inc_or_zero intoption =
    case intoption of
            NONE => 0
        |   SOME i => i+1;

fun sum_list xs =
    case xs of
        [] => 0
        | x::xs' => x + sum_list xs';

fun append (xs, ys) =
    case xs of
        [] => ys
        | x::xs' => x::append(xs', ys)


fun append (xs,ys) =
    case xs of
        x::xs' => x :: append(xs',ys)
      | [] => ys;

