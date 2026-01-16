fetch("C:\Users\ewf08\OneDrive\Desktop\CS-212\project-8\data.json")
    then(response => response.json())
    then(data => {

    const personalInfo = data.personalInfo;
    const skills = data.skills;
    const education = data.education;
    const projects = data.projects;
    const experience = data.experience;
    const links = data.activeLinks;

    //stuff for personal info
    const personalDiv = document.getElementById("personalInfo");
    personalDiv.innerHTML =`
    <h2>${data.personalInfo.name}</h2>
    <p>${data.personalInfo.email}</p>
    <p>${data.personalInfo.phone}</p>
    <p>${data.personalInfo.location}</p>
    `;   

    //stuff for skills 
    const skillsDiv = document.getElementById("skills");
    skills.innerHTML = `
    <li></li>
    `;




    //stuff for education
    const degree = education.degree;
    const institution = education.institution;
    const fieldOfStudy = education.fieldOfStudy;
    const graduationYear = education.graduationYear;



    //stuff for projects
    const projectName = projects.name;
    const technologies = projects.technologies;
    const description = projects.description;



    //stuff for experience
    const company = experience.company;
    const position = experience.position;
    const responsibilities = experience.responsibilities;
    const startDate = experience.startDate;
    const endDate = experience.endDate;

    //stuff for links
    const linkName = activeLinks.name;
    const url = activeLinks.url;
    const isActive = activeLinks.isActive;


    })
    .catch(error => console.error("Error:", error));