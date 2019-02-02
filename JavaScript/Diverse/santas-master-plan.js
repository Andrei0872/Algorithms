// https://www.codewars.com/kata/santas-master-plan/train/javascript

function getAttendees(peopleInvited, responses) {
    return peopleInvited.filter(person => {
        return responses.find(response => response.name === person && response.response === 'accepted')
            || !responses.some(({ name }) => name === person )
    });
}

const r = getAttendees(['Easter Bunny', 'Tooth Fairy', 'Frosty the Snowman', 'Jack Frost'],
    [
        { name: 'Easter Bunny', response: 'declined' },
        { name: 'Jack Frost', response: 'declined' },
        { name: 'Tooth Fairy', response: 'accepted' }
    ]);// => returns ['Tooth Fairy', 'Frosty the Snowman']

console.log(r) // [ 'Tooth Fairy', 'Frosty the Snowman' ]​​​​​