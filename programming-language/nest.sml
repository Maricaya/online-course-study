fun countup_from1 (x: int) =
    let
	fun count (from: int) =
            if from = x
            then x::[]
            else from::count(from+1);
    in
	count(1)
    end;

(* fn: int list -> int option *)
fun good_max (xs: int list) =
    if null xs
    then NONE
    else
	let val tl_ans = good_max(tl xs)
	in if isSome tl_ans andalso valOf tl_ans > hd xs
	    then tl_ans
	    else SOME(hd xs)
	end;
	    

fun max2 (xs: int list) =
    if null xs
    then NONE
    else let
    	    fun max_nonempty (xs: int list) =
		if null (tl xs)
		then hd xs
		else let val tl_ans = max_nonempty(tl xs)
		     in
			 if hd xs > tl_ans
			 then hd xs
			 else tl_ans
		     end
	in
	    SOME (max_nonempty xs)
    end;


(*
andalso
orelse
not
*)
