data List a  = Empty | Cons a (List a) deriving Show
mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f (x : xs) = (f x) : (mymap f xs)

f1 = \x -> x + 1
f2 = \x y -> x*y
f3 = f2 2

p1 = ("Turing", (1912, "UK"))  -- Fixed: closed the string quote
p2 = ("Neumann", (1903, "Hungary"))
dict = [p1, p2]

-- lookup is already defined in Prelude, so you don't need to redefine it
-- But if you want to define it yourself:
-- lookup :: Eq a => a -> [(a,b)] -> Maybe b
-- lookup _ [] = Nothing
-- lookup key ((k,v):rest) = if key == k then Just v else lookup key rest

-- Data declaration should be at top level (already defined in Prelude)
-- data Maybe a = Just a | Nothing

lookup_year :: String -> [(String, (Integer, String))] -> Integer  -- Fixed: underscore instead of hyphen
lookup_year key alst = case (lookup key alst) of  -- Fixed: added "of"
    Just v -> fst v      -- Fixed: fst v to get the year from the tuple
    Nothing -> error "Key not found"  -- Fixed: added error message string

data Maybe a = Just a | Nothing
(Just 1)
Nothing

delete :: Integer -> [(String, (Integer, String))] -> [(String, (Integer, String))] 
delete year [] = []
delete year (x@(_, (y, _)) : xs) 
    | year == y = delete year xs      -- if year matches, skip this entry
    | otherwise = x : delete year xs  -- if not, keep this entry