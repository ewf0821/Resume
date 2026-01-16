let portfolioData = {};




//personal info section
let personalInfo = {};
personalInfo.name = "test user";
personalInfo.email = "abc@123.com";
personalInfo.phone = "1 123-456-7890";
personalInfo.location = "location";
portfolioData.personalInfo = personalInfo;

//skills section
const technicalSkills = ["HTML","CSS","JavaScript","C","Python"];
const softSkills = ["Communication","Public Speakinig","Management"];
const skills = technicalSkills.concat(softSkills);
skills.sort();
portfolioData.skills = skills;


//education section
const educationPrototype = {
    degree:"degree",
    institution: "institution",
    fieldOfStudy: "CS",
    graduationYear: "2025"
}
const educationSection = [];
const objectFromPrototype = Object.assign({}, educationPrototype);
for(let i = 0; i <  3; i++){
    educationSection.push(objectFromPrototype);
}

portfolioData.education = educationSection;

//Experience section
const experiencePrototype = {
    company: "Company title", 
    position: "Software Developer",
    responsibilities: "Responsibilites", 
    startDate: "01-01-1999",
    endDate: "12-12-2000" 
}

const experienceSection = [];
const objectFromExperience = Object.assign({}, experiencePrototype);
for(let i = 0; i < 3; i++){
    experienceSection.unshift(objectFromExperience);
}
portfolioData.experience = experienceSection;


//media links section
const mediaLinks = [
    {name: "LinkedIn", url: "profile URL", isActive: true},
    {name: "Facebook", url: "profile URL", isActive: false},
    {name: "Instagram", url: "profile URL", isActive: false},
    {name: "Resume", url: "Resume URL", isActive: true}
]

let filteredLinks = mediaLinks.filter(mediaLinks => mediaLinks.isActive);

portfolioData.activeLinks = filteredLinks;

console.log(portfolioData);

