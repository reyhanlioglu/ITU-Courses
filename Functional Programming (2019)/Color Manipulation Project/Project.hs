module Project where
import Prelude
import Data.Fixed

-- PART 1

--This function returns the maximum of 3 inputs
maxThree :: Float -> Float -> Float -> Float
maxThree x y z
  | x>=y && x>=z = x
  | y>=z         = y
  | otherwise    = z

--This function returns the minimum of 3 inputs
minThree :: Float -> Float -> Float -> Float
minThree x y z
  | x<=y && x<=z = x
  | y<=z         = y
  | otherwise    = z

-- This function calculates delta in the formula
calcDelta :: Float->Float->Float->Float
calcDelta r g b = (maxThree r g b) - (minThree r g b)

-- This function calculates hue value according to formula
calcHue :: Float->Float->Float->Float
calcHue r g b
  | (calcDelta r g b) == 0   = 0
  | (maxThree r g b) == r    = (60 *( ((g-b)/(calcDelta r g b)) `mod'`6 ))
  | (maxThree r g b) == g    = (60 *( ((b-r)/(calcDelta r g b)) + 2))
  | (maxThree r g b) == b    = (60 *( ((r-g)/(calcDelta r g b)) + 4 ))

-- This function calculates saturation value according to formula
calcSat :: Float->Float->Float->Float
calcSat r g b
  | (maxThree r g b) == 0  = 0
  | otherwise              = (100*(calcDelta r g b) / (maxThree r g b))


normalize :: Float->Float
normalize x = x/255

--This function takes a RGB triple and convert to a HSV triple
rgb2hsv :: (Float,Float,Float)->(Float,Float,Float)
rgb2hsv  (r,g,b) = (h, s, v)
  where
    h = calcHue (normalize r) (normalize g) (normalize b)
    s = calcSat (normalize r) (normalize g) (normalize b)
    v = (100*maxThree (normalize r) (normalize g) (normalize b))


-- PART 2

-- Calculation function of hsv2rgb
calcRGB :: Float->Float->Float->(Float,Float,Float)
calcRGB  h s v
  | 0<=h && h<60    = (c, x, 0)
  | 60<=h && h<120  = (x, c, 0)
  | 120<=h && h<180 = (0, c, x)
  | 180<=h && h<240 = (0, x, c)
  | 240<=h && h<300 = (x, 0, c)
  | 300<=h && h<=360= (c, 0, x)
  where
    c = v*s
    x = c*(1 - (abs(( (divX h) `mod'` 2) -1))) 
    divX :: Float -> Float
    divX x = x/60


--This function takes a HSV triple and convert to a RGB triple
hsv2rgb :: (Float,Float,Float)-> (Float,Float,Float)
hsv2rgb (h,s,v) = (r,g,b)
  where
    m = (v/100)-((v/100)*(s/100))
    r = ((get1th(calcRGB h (s/100) (v/100)) + m)*255)
    g = ((get2nd(calcRGB h (s/100) (v/100)) + m)*255)
    b = ((get3rd(calcRGB h (s/100) (v/100)) + m)*255)
    get1th (x,_,_) = x
    get2nd (_,x,_) = x
    get3rd (_,_,x) = x


-- PART 3

-- Converter
hexToInt:: String -> String
hexToInt h
  | h == "0" = "0"
  | h == "1" = "1"
  | h == "2" = "2"
  | h == "3" = "3"
  | h == "4" = "4"
  | h == "5" = "5"
  | h == "6" = "6"
  | h == "7" = "7"
  | h == "8" = "8"
  | h == "9" = "9"
  | h == "A" = "10"
  | h == "B" = "11"
  | h == "C" = "12"
  | h == "D" = "13"
  | h == "E" = "14"
  | h == "F" = "15"

-- This function converts HTML color into RGB triple
name2rgb :: String -> (Float,Float,Float)
name2rgb name = ((toR name) , (toG name) , (toB name))
  where
    toR n = (read (hexToInt(drop 1 (take 2 n))):: Float) *16 + (read (hexToInt(drop 2 (take 3 n))):: Float)
    toG n = (read (hexToInt(drop 3 (take 4 n))):: Float) *16 + (read (hexToInt(drop 4 (take 5 n))):: Float)
    toB n = (read (hexToInt(drop 5 (take 6 n))):: Float) *16 + (read (hexToInt(drop 6 (take 7 n))):: Float)



-- PART 4

hsvGradient :: (Float,Float,Float)->(Float,Float,Float)->Float -> [(Float,Float,Float)]
hsvGradient (h1,s1,v1) (h2,s2,v2) n = (zip3 hArray sArray  vArray)
  where
  hArray = [h1,(h1+((h2-h1)/n))..h2]
  sArray = [s1,(s1+((s2-s1)/n))..s2]
  vArray = [v1,(v1+((v2-v1)/n))..v2]



-- PART 5

hName :: Float -> String
hName h
  | h<15    = "red"
  | h==15   = "reddish"
  | h<=45   = "orange"
  | h<=70   = "yellow"
  | h<=79   = "lime"
  | h<=163  = "green"
  | h<=193  = "cyan"
  | h<=240  = "blue"
  | h<=260  = "indigo"
  | h<=270  = "violet"
  | h<=291  = "purple"
  | h<=327  = "magenta"
  | h<=344  = "rose"
  | h<=360  = "red"


sName :: Float -> String
sName s
  | s<4    = "grey"
  | s<=10  = "almost grey"
  | s<=30  = "very unsaturated"
  | s<=46  = "unsaturated"
  | s<=60  = "rather unsaturated"
  | s<=80  = "saturated"
  | s<=90  = "rather saturated"
  | s<=100 = "very saturated"

vName :: Float -> String
vName v
  | v<10   = "almost black"
  | v<=22  = "very dark"
  | v<=30  = "dark"
  | v<=60  = "normal"
  | v<=80  = "light"
  | v<=94  = "very light"
  | v<=100 = "almost white"


hsv2desc :: (Float,Float,Float) -> String
hsv2desc (h,s,v) = "Hue: " ++ hName h ++ ", Saturation: " ++ sName s ++ ", Lightness: " ++ vName v


-- PART 6

showTriples :: (Show h, Show s, Show v) => (h,s,v) -> String
showTriples (h,s,v) = "HSV: ("++(show h) ++ "," ++ (show s)++"," ++ (show v)++") , RGB: "++(show hsvResult)
  where
    hsvResult =hsv2rgb (((read (show h))::Float),((read (show s))::Float), ((read (show v))::Float))


printGradient :: IO ()
printGradient = do
  putStrLn "Enter two color name:"
  do
    color1 <- getLine
    do
      color2 <- getLine
      do
        putStrLn("Enter number of steps:")
        n <- getLine
        putStrLn ("Gradients from color1= " ++ color1 ++ " to color2= " ++ color2++" in steps:"++n++";")
        mapM_ (putStrLn . showTriples) (hsvGradient (rgb2hsv(name2rgb color1)) (rgb2hsv(name2rgb color2)) ((read n)::Float) )   


-- PART 7

-- Converter
intToHex:: Integer -> String
intToHex h
  | h == 0 = "0"
  | h == 1 = "1"
  | h == 2 = "2"
  | h == 3 = "3"
  | h == 4 = "4"
  | h == 5 = "5"
  | h == 6 = "6"
  | h == 7 = "7"
  | h == 8 = "8"
  | h == 9 = "9"
  | h == 10 = "A"
  | h == 11 = "B"
  | h == 12 = "C"
  | h == 13 = "D"
  | h == 14 = "E"
  | h == 15 = "F"

-- Function which takes RGB triple and returns HTML color name of it
rgb2html :: (Float,Float,Float) -> String
rgb2html (r,g,b) = "#" ++ convertToHex r ++ convertToHex g ++ convertToHex b
  where
    convertToHex :: Float -> String
    convertToHex s = intToHex((floor(s/16))`mod`16)++ intToHex((floor s)`mod`16)

-- Function which takes HSV triple and returns HTML color name of it
hsv2html :: (Float,Float,Float) -> String
hsv2html (h,s,v) = rgb2html(hsv2rgb(h,s,v))