// https://www.codewars.com/kata/meeting/train/javascript

function meeting(s) {
    return '(' + s.toUpperCase().split(';')
        .map(names => names.split(':').join(', '))
        .sort()
        .join(')(') +
        ')'
}


console.log(meeting(
    "Alexis:Wahl;John:Bell;Victoria:Schwarz;Abba:Dorny;Grace:Meta;Ann:Arno;Madison:STAN;Alex:Cornwell;Lewis:Kern;Megan:Stan;Alex:Korn",
    "(ARNO, ANN)(BELL, JOHN)(CORNWELL, ALEX)(DORNY, ABBA)(KERN, LEWIS)(KORN, ALEX)(META, GRACE)(SCHWARZ, VICTORIA)(STAN, MADISON)(STAN, MEGAN)(WAHL, ALEXIS)"
))