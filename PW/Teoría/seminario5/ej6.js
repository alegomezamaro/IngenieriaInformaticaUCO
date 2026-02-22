const payload = {
  meta: { version: 3, locale: 'es-ES' },
  course: {
    id: 42,
    title: 'JS Básico',
    teachers: [{ id: 1, name: 'Ada' }, { id: 2, name: 'Alan' }, { id: 3, name: 'Grace'}],
    schedule: ['lun 10:00', 'mié 12:00', 'vie 09:00'],
    tags: ['js', 'web', 'intro'],
    // level: "advanced"
    // course.level podría venir undefined
  },
  // payload.audit no siempre viene 
};

const { id: CourseId,
        title: name,
        level = "begginer"} = payload.course;

console.log(CourseId, name, level);

const {schedule: [first, ...tail]} = payload.course;
const {teachers: [lead, ,backup]} = payload.course;

console.log(first, tail);
console.log(lead, backup);

const {meta: {locale, ...metaRest}} = payload;

console.log(locale, metaRest);

const {tags: [primerTag, ...otrosTags] = ["general"] } = payload.course;

console.log(primerTag, ...otrosTags);
