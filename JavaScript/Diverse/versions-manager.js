
// https://www.codewars.com/kata/versions-manager/train/javascript

//* Versions Manager

/**
 * release() - return the version
 * major() - increase the major version and reset patch
 * minor() - increase the minor version and reset patcg
 * patch() - increase patch
 * rollback() - undo a previous version change
 * @param {string} version the given version
 * @param {array} previous store previous version
 */
const vm = (version = '0.0.1', prev = []) => {
    version = (() => {
        let v = version.split('.').splice(0.3);
        for(let i of v) {
            if(isNaN(i)) {
                throw new Error('Error occured while parsing version!');
            }
        }
        v.length = 3;
        v = [... v].map(elem => elem === undefined ? 0 : +elem);
        return v.join('.') === '0.0.0' ? [0,0,1] : v;
    })();

    // Save previous version
    const update = v => { prev.push(version), version = v };
    
    const output = {
        release : () => version.join('.'),
        major : () => { update([version[0] +1, 0, 0]); return output;},
        minor : () => { update([version[0],version[1] + 1, 0]); return output;},
        patch : () => { update([version[0],version[1], version[2] + 1]); return output},
        rollback : () => {
            if(!prev.length) throw new Error('Cannot rollback!');
            version = prev.pop();
            return output;
        }
    };

    return output;
}


console.log(vm('1.2.3').patch().minor().rollback().release(), '1.2.4');
console.log(vm().release(), '0.0.1');
console.log(vm('1.2.3').release(), '1.2.3');
console.log(vm('1.2.3.4').release(), '1.2.3');
console.log(vm('1').release(), '1.0.0');
console.log(vm('1.1').release(), '1.1.0');
console.log(vm('1.2.3.d').release(), '1.2.3');