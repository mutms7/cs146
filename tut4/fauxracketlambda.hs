-- ((fun (x) (+ x 1)) 2)
-- ((fun (x) (fun (x) (+ x x)) 2) 3)
-- start innermost

data Expr = (Fun String Expr)
| (App Expr Expr)
| (With (String,Expr) Expr)
| (Var String)
| (Lit Integer)
| (Bin Op Expr Expr)

interp:: Expr -> Expr
interp x @ (Lit _) = x
interp x @ (Var _) = x
interp x @ (Fun _ _) = x
interp (With (var, val) body) = interp (App (Fun var body) val)